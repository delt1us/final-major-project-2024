/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-07-05 15:41:09
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-07-10 21:48:47
 */

using UnityEngine;

public class PlayerCollisionController : MonoBehaviour
{
    private HealthController healthController;

    void Start()
    {
        healthController = GetComponent<HealthController>();
        if (healthController == null)
        {
            Debug.Log("HealthController not found");
        }
    }

    void OnTriggerStay2D()
    {
        // Debug.Log("Trigger entered");
        healthController.TakeDamage(1.0f);
    }
}
