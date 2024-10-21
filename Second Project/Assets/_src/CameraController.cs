/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-06-25 18:07:22
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-07-10 20:31:49
 */

// This is no longer used
using UnityEngine;

public class CameraController : MonoBehaviour
{
    [SerializeField]
    private BoxCollider2D followTargetCollider2D = null;
    private Camera cam = null;

    private void Start()
    {
        cam = GetComponent<Camera>();
        if (cam == null)
            Debug.LogError("Camera not found");
    }

    private void FixedUpdate()
    {
        if (followTargetCollider2D != null)
        {
            Vector3 targetPosition = followTargetCollider2D.bounds.center;
            transform.SetPositionAndRotation(
                new Vector3(
                    targetPosition.x - cam.rect.width * 0.5f,
                    targetPosition.y + cam.rect.height * 0.5f,
                    transform.position.z
                ),
                transform.rotation
            );
        }
    }
}
