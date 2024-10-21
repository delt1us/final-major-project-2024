/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-07-05 15:28:54
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-07-10 21:47:48
 */

using UnityEngine;

public class HealthController : MonoBehaviour
{
    [SerializeField]
    private CharacterSO characterSO;

    [SerializeField]
    private UISO uiSO;

    private float _health = 1.0f;
    public float health
    {
        get { return _health; }
        private set
        {
            _health = value;
            uiSO.textDict[DebugTextType.PlayerHealth] = $"Health: {health.ToString()}";
        }
    }

    // Iframes but it is handled in FixedUpdate() so it isn't actually frames
    private int _immunity = 0;
    private int immunity
    {
        get { return _immunity; }
        set
        {
            _immunity = value;
            uiSO.textDict[DebugTextType.PlayerImmunity] = $"Immunity: {immunity.ToString()}";
        }
    }

    private int maxImmunity = 60;

    void Start()
    {
        if (characterSO == null)
            Debug.Log("Character Scriptable Object not found");
        if (uiSO == null)
            Debug.Log("UI Scriptable Object not found");
        // Set them to themselves to update debug display preemptively
        immunity = characterSO.immunityDuration;
        health = characterSO.maxHealth;
    }

    void FixedUpdate()
    {
        if (immunity > 0)
            immunity--;
    }

    public void TakeDamage(float damage)
    {
        if (immunity != 0)
            return;
        immunity = maxImmunity;
        health -= damage;
    }
}
