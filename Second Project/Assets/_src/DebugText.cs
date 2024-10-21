/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-07-02 23:27:43
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-07-10 21:47:24
 */

using System;
using TMPro;
using UnityEngine;

public class DebugText : MonoBehaviour
{
    [SerializeField]
    private UISO uiSO;

    private TMP_Text tmpText;

    void Start()
    {
        if (uiSO == null)
            Debug.Log("UI Scriptable Object not found");

        tmpText = GetComponent<TMP_Text>();
        if (tmpText == null)
            Debug.Log("TMP_Text component not found");
    }

    void Update()
    {
        tmpText.text = String.Join("\n", uiSO.textDict.Values);
    }
}
