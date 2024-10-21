/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-06-25 16:59:18
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-07-10 21:49:06
 */

using System;
using UnityEngine;
using UnityEngine.InputSystem;

public class PlayerMovementController : MonoBehaviour
{
    [SerializeField]
    private CharacterSO characterSO;

    [SerializeField]
    private UISO uiSO;

    public Action onMoved;
    private Vector2 movingDirection;
    private Animator animator = null;
    private bool flipped = false;

    void Start()
    {
        if (characterSO == null)
            Debug.Log("Character Scriptable Object not found");
        if (uiSO == null)
            Debug.Log("UI Scriptable Object not found");

        uiSO.textDict.Add(DebugTextType.PlayerPosition, "");

        animator = GetComponent<Animator>();
        if (animator == null)
            Debug.Log("Animator component not found");
    }

    void FixedUpdate()
    {
        MoveTransform();
        UpdateAnimator();
    }

    // Called using unity events by the character controller
    public void Move(InputAction.CallbackContext context)
    {
        movingDirection = context.ReadValue<Vector2>();
        // Debug.Log($"movingDirection: {movingDirection}");
    }

    void UpdateAnimator()
    {
        // Update animator xVelocity variable to set animation state
        if (movingDirection.x != 0 && animator.GetFloat("xVelocity") == 0)
            animator.SetFloat("xVelocity", Math.Abs(movingDirection.x));
        // If not moving but animator thinks character is moving, set animator.xVelocity to 0
        else if (movingDirection.x == 0 && animator.GetFloat("xVelocity") != 0)
            animator.SetFloat("xVelocity", 0);
    }

    void MoveTransform()
    {
        // Add characterSO.movementSpeed * direction to position
        // Leave z constant
        if (movingDirection.x != 0 || movingDirection.y != 0)
        {
            transform.SetPositionAndRotation(
                new Vector3(
                    transform.position.x + characterSO.movementSpeed * movingDirection.x,
                    transform.position.y + characterSO.movementSpeed * movingDirection.y,
                    transform.position.z
                ),
                transform.rotation
            );
            onMoved?.Invoke();
        }
        // If moving in opposite direction of flip, flip transform
        if (movingDirection.x < 0 && !flipped || movingDirection.x > 0 && flipped)
        {
            flipped = !flipped;
            FlipTransform();
        }

        uiSO.textDict[DebugTextType.PlayerPosition] = $"position: {transform.position}";
    }

    // Flip transform to also flip the sprite
    void FlipTransform()
    {
        transform.localScale = new Vector3(
            transform.localScale.x * -1,
            transform.localScale.y,
            transform.localScale.z
        );
    }
}
