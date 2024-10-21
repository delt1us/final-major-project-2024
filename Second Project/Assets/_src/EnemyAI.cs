/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-07-05 14:14:32
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-07-11 21:23:34
 */

using UnityEngine;

public class EnemyAI : MonoBehaviour
{
    [SerializeField]
    private CharacterSO characterSO;

    public Transform target;

    void Start()
    {
        if (characterSO == null)
            Debug.Log("Character Scriptable Object not found");
    }

    void FixedUpdate()
    {
        transform.position = Vector3.MoveTowards(
            transform.position,
            target.position,
            characterSO.movementSpeed
        );
    }
}
