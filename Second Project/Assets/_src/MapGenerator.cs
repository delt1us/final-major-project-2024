/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-07-02 23:27:41
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-07-10 21:48:33
 */

using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Tilemaps;

public class MapGenerator : MonoBehaviour
{
    // TODO make it choose a chunk at random (given a seed?)
    [SerializeField]
    private GameObject chunkPrefab;

    [SerializeField]
    private Player player;

    [SerializeField]
    private int playerChunkGenerationRadius = 1;

    [SerializeField]
    private UISO uiSO;

    // Chunks must be squares
    private int chunkSize;
    private Dictionary<(int, int), GameObject> chunksDict;

    void Start()
    {
        if (uiSO == null)
            Debug.Log("UI Scriptable Object not found");

        uiSO.textDict.Add(DebugTextType.PlayerPositionChunks, "");

        if (!CheckRequiredSerializeFields())
            return;

        chunksDict = new Dictionary<(int, int), GameObject>();
        // TODO check if all chunks are same size (when chunk randomisation is implemented)
        if (!CheckChunksDimensions())
            return;

        GenerateInitialChunks();
        MovePlayerToCenter();
    }

    void OnEnable()
    {
        // Subscribe to character moving event
        if (player == null)
        {
            Debug.Log("Player not found");
            return;
        }

        PlayerMovementController movementController =
            player.gameObject.GetComponentInChildren<PlayerMovementController>();
        if (movementController != null)
        {
            movementController.onMoved += GenerateNewChunks;
            movementController.onMoved += ToggleChunksBasedOnDistnace;
        }
        else
            Debug.Log("PlayerMovementController component not found");
    }

    void OnDisable()
    {
        if (player == null)
            return;

        PlayerMovementController movementController =
            player.gameObject.GetComponentInChildren<PlayerMovementController>();
        if (movementController != null)
        {
            movementController.onMoved -= GenerateNewChunks;
            movementController.onMoved -= ToggleChunksBasedOnDistnace;
        }
    }

    void Update()
    {
        uiSO.textDict[DebugTextType.PlayerPositionChunks] = $"chunk: {GetPlayerChunk()}";
    }

    // Turns off all chunks further than the radius and turns any on in the radius
    void ToggleChunksBasedOnDistnace()
    {
        Vector2Int playerChunk = GetPlayerChunk();

        Vector2Int lowerBound = new Vector2Int(
            playerChunk.x - playerChunkGenerationRadius,
            playerChunk.y - playerChunkGenerationRadius
        );
        Vector2Int upperBound = new Vector2Int(
            playerChunk.x + playerChunkGenerationRadius,
            playerChunk.y + playerChunkGenerationRadius
        );

        // Use keys so that their positions can be compared
        foreach ((int, int) chunkKey in chunksDict.Keys)
        {
            // Debug.Log(
            //     $"{lowerBound.x} <= {chunkKey.Item1} && {chunkKey.Item1} <= {upperBound.y} && {lowerBound.y} <= {chunkKey.Item2} && {chunkKey.Item2} <= {upperBound.y}"
            // );

            // If between lower and upper bound for both x and y values
            if (
                lowerBound.x <= chunkKey.Item1
                && chunkKey.Item1 <= upperBound.x
                && lowerBound.y <= chunkKey.Item2
                && chunkKey.Item2 <= upperBound.y
            )
                chunksDict[chunkKey].SetActive(true);
            else
                chunksDict[chunkKey].SetActive(false);
        }
    }

    void MovePlayerToCenter()
    {
        // Move player to the center of 0,0
        player.transform.SetPositionAndRotation(
            new Vector3(
                0.5f * (chunkSize - player.transform.lossyScale.x),
                0.5f * (-chunkSize - player.transform.lossyScale.y),
                0
            ),
            player.transform.rotation
        );
    }

    void GenerateInitialChunks()
    {
        // Generate in 3x3 grid around 0,0
        for (int x = -1; x < 2; x++)
        {
            for (int y = -1; y < 2; y++)
            {
                GenerateChunk(x, y);
            }
        }
    }

    // Check if new chunks need to be generated
    void GenerateNewChunks()
    {
        Vector2Int playerChunk = GetPlayerChunk();
        for (
            int x = playerChunk.x - playerChunkGenerationRadius;
            x <= playerChunk.x + playerChunkGenerationRadius;
            x++
        )
        {
            for (
                int y = playerChunk.y - playerChunkGenerationRadius;
                y <= playerChunk.y + playerChunkGenerationRadius;
                y++
            )
            {
                if (!chunksDict.ContainsKey((x, y)))
                {
                    GenerateChunk(x, y);
                }
            }
        }
    }

    Vector2Int GetPlayerChunk()
    {
        // Integer division
        Transform character = player
            .GetComponentInChildren<PlayerMovementController>()
            .gameObject.transform;
        int x = (int)character.position.x / chunkSize;
        int y = (int)character.position.y / chunkSize;
        // Debug.Log(
        //     $"Transform position: ({character.position.x},{character.position.y})\nchunkSize: {chunkSize}\nPlayer chunk: ({x},{y})"
        // );
        return new Vector2Int(x, y);
    }

    // x, y are chunk coordinates (not world coordinates)
    void GenerateChunk(int x, int y)
    {
        // Debug.Log($"Generating chunk at {x},{y} ({x * chunkSize},{y * chunkSize})");
        GameObject chunkInstance = Instantiate(
            chunkPrefab,
            new Vector3(x * chunkSize, y * chunkSize, 1),
            Quaternion.identity,
            transform
        );
        chunksDict.Add((x, y), chunkInstance);
    }

    bool CheckRequiredSerializeFields()
    {
        if (player == null || chunkPrefab == null)
        {
            Debug.Log("Player Movement Controller " + (player ? " " : "not ") + " found");
            Debug.Log("Chunk Prefab " + (chunkPrefab ? " " : "not ") + " found");
            return false;
        }
        return true;
    }

    bool CheckChunksDimensions()
    {
        // Set chunkSize before just to save accessing width twice
        Grid grid = chunkPrefab.GetComponentInChildren<Grid>();
        if (grid == null)
        {
            Debug.Log("Grid component not found");
            return false;
        }
        Tilemap tilemap = grid.GetComponentInChildren<Tilemap>();
        if (tilemap == null)
        {
            Debug.Log("Tilemap component not found");
            return false;
        }

        Debug.Log($"grid.cellSize: ({grid.cellSize.x},{grid.cellSize.y})");
        Debug.Log($"tilemap.size: ({tilemap.size.x},{tilemap.size.y})");
        chunkSize = (int)Math.Abs(grid.cellSize.x * tilemap.size.x);
        int height = (int)Math.Abs(grid.cellSize.y * tilemap.size.y);
        if (chunkSize != height)
        {
            Debug.Log($"Chunk is not square ({chunkSize},{height})");
            return false;
        }
        Debug.Log($"Chunk dimensions good ({chunkSize},{height})");
        return true;
    }
}
