#ifndef _CAMERA
#define _CAMERA

// Initialize Camera module before anything else
void Camera_init(void);
// Cleanup procedures for Camera module
void Camera_cleanup(void);

// Turn on/off camera capturing
void Camera_on(void);
void Camera_off(void);

// Blocking call, will loop infinitely until shutdown is called
void Camera_mainloop(void);

#endif