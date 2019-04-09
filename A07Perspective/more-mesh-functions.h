// This file contains functions that should be added to your Mesh class.
// Don't actually put this file into your project -- just copy from it.

  Transform
  getWorld () const;

  // Key: "1"
  void
  moveRight (float distance);

  // Key: "2"
  void
  moveUp (float distance);

  void
  moveBack (float distance);

  void
  moveLocal (float distance, const Vector3& localDirection);

  // Key: "3"
  void
  moveWorld (float distance, const Vector3& worldDirection);

  // Key: "4"
  void
  pitch (float angleDegrees);

  // Key: "5"
  void
  yaw (float angleDegrees);

  // Key: "6"
  void
  roll (float angleDegrees);

  void
  rotateLocal (float angleDegrees, const Vector3& axis);

  // Key: "7"
  void
  alignWithWorldY ();

  // Key: "8"
  void
  scaleLocal (float scale);

  void
  scaleLocal (float scaleX, float scaleY, float scaleZ);
    
  // Key: "9"
  void
  scaleWorld (float scale);

  void
  scaleWorld (float scaleX, float scaleY, float scaleZ);

  // Key: "0"
  void
  shearLocalXByYz (float shearY, float shearZ);

  void
  shearLocalYByXz (float shearX, float shearZ);

  void
  shearLocalZByXy (float shearX, float shearY);
