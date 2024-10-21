/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-07-10 20:19:03
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-07-11 23:25:27
 */

using System.Collections.Generic;
using UnityEngine;

public class EnemySpawner : MonoBehaviour
{
    [SerializeField]
    private Camera mainCamera;

    [SerializeField]
    private List<GameObject> enemyPrefabs;

    [SerializeField]
    private int maxEnemyCount = 1;

    // 1/n Multiplier for spawnDelay
    [SerializeField]
    private float spawnRate = 1.0f;

    [SerializeField]
    private Transform playerTransform;

    [SerializeField]
    private int spawnOffsetFromEdge = 100;

    // FixedUpdates between each spawn
    private int spawnDelay = 30;
    private int framesSinceLastSpawn = 0;

    private List<GameObject> spawnedEnemies;

    void Start()
    {
        spawnedEnemies = new List<GameObject>();

        if (playerTransform == null)
            Debug.Log("Player transform not set");

        if (enemyPrefabs == null || enemyPrefabs.Count == 0)
            Debug.Log("Enemy prefabs list empty");

        spawnDelay = (int)((float)spawnDelay / spawnRate);
    }

    void FixedUpdate()
    {
        if (framesSinceLastSpawn == 0 && spawnedEnemies.Count < maxEnemyCount)
        {
            SpawnEnemy();
            framesSinceLastSpawn = spawnDelay;
        }
        else if (framesSinceLastSpawn != 0)
            framesSinceLastSpawn--;
    }

    void SpawnEnemy()
    {
        // Unfold perimeter and find a random point on it
        float randomPoint = Random.Range(0, 2.0f * (Screen.width + Screen.height));
        Vector2 randomPos = new Vector2();
        // Top edge
        if (randomPoint < Screen.width)
        {
            // Offset it in the axis that it isnt random in for this particular edge
            randomPos = new Vector2(randomPoint, -spawnOffsetFromEdge);
        }
        // Left edge
        else if (randomPoint < Screen.width + Screen.height)
        {
            randomPos = new Vector2(-spawnOffsetFromEdge, randomPoint - Screen.width);
        }
        // Right egde
        else if (randomPoint < Screen.width + Screen.height * 2.0f)
        {
            randomPos = new Vector2(
                Screen.width + spawnOffsetFromEdge,
                randomPoint - Screen.width - Screen.height
            );
        }
        // Bottom edge
        else
        {
            randomPos = new Vector2(
                randomPoint - Screen.width - 2.0f * Screen.height,
                Screen.height + spawnOffsetFromEdge
            );
        }

        Debug.Log($"Random position: {randomPos}");
        Vector3 spawnPos = mainCamera.ScreenToWorldPoint(randomPos);
        spawnPos.z = 0;

        // Spawn random prefab at spawnPos as child of this GameObject. Add the GameObject to the list
        spawnedEnemies.Add(
            Instantiate(
                enemyPrefabs[Random.Range(0, enemyPrefabs.Count)],
                spawnPos,
                Quaternion.identity,
                transform
            )
        );
        spawnedEnemies[spawnedEnemies.Count - 1].GetComponentInChildren<EnemyAI>().target =
            playerTransform;
    }
}
