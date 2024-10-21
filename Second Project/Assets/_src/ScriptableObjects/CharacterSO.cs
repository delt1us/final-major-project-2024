/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-07-10 20:43:15
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-07-10 21:01:53
 */

using UnityEngine;

[CreateAssetMenu(fileName = "CharacterSO", menuName = "ScriptableObjects/Character")]
public class CharacterSO : ScriptableObject
{
    public float movementSpeed = 0.0f;
    public int maxHealth = 100;

    // Fixed update ticks
    public int immunityDuration = 0;
}
