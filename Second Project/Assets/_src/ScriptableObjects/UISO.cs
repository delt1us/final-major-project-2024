/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-07-10 20:43:08
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-07-10 21:45:54
 */

using System.Collections.Generic;
using UnityEngine;

public enum DebugTextType
{
    PlayerPosition,
    PlayerPositionChunks,
    PlayerHealth,
    PlayerImmunity
}

[CreateAssetMenu(fileName = "UISO", menuName = "ScriptableObjects/UI")]
public class UISO : ScriptableObject
{
    public Dictionary<DebugTextType, string> textDict;

    void OnEnable()
    {
        textDict = new Dictionary<DebugTextType, string>();
    }
}
