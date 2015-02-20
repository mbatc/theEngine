#pragma once

struct Vector3
{
	float x, y, z;
};

class Transform
{
public:
	Transform();

	//------------------------------------------
	//INLINE METHODS
	Vector3 GetTranslation(){ return Translation; }
	Vector3 GetRotation(){ return Rotation; }
	Vector3 GetScale(){ return Scale; }
	
	void SetTranslation(float x, float y, float z){ Translation.x = x; Translation.y = y; Translation.z = z; }
	void SetRotation(float x, float y, float z){ Rotation.x = x; Rotation.y = y; Rotation.z = z; }
	void SetScale(float x, float y, float z){ Scale.x = x; Scale.y = y; Scale.z = z; }

	void Update();

private:
	Vector3 Translation;
	Vector3 Rotation;
	Vector3 Scale;
};