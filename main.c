#include "Sample0.h"

using namespace Wire;

WIRE_APPLICATION(cube);		// This macro creates our user application.

//----------------------------------------------------------------------------
Bool Sample0::OnPrecreate()
{
	if (!Parent::OnPrecreate())
	{
		return false;
	}

	return true;
}

//----------------------------------------------------------------------------
Bool Sample0::OnInitialize()
{
	// This function is called by the framework after the renderer was
	// initialized, but before the rendering loop starts.

	if (!Parent::OnInitialize())
	{
		return false;
	}

	// Put all your initializations here.

	// We create a cube and reference it using a smart pointer. The smart
	// pointer automatically deletes the object when it goes out of scope
	// and no other references to the object exist. In this case deletion
	// will happen when Sample0 is being destructed.
	// Creation of Wire::RenderObject is explained in detail in Sample1.
	// StandardMesh is just a helper class creating various geometric objects.
	mspCube = StandardMesh::CreateCube8(/* number of RGB(A) channels */ 4);

	// Create a camera for rendering
	Vector3F cameraLocation(0.0F, 0.0F, 10.0F);
	Vector3F viewDirection(0.0F, 0.0F, -1.0F);
	Vector3F up(0.0F, 1.0F, 0.0F);
	mspCamera = WIRE_NEW Camera(cameraLocation, viewDirection, up);

	return true;
}

//----------------------------------------------------------------------------
void Sample0::OnIdle()
{
	// The render loop. Called by the main loop.

	// Rotate the cube and render it.
	Transformation transformation;
	Matrix3F rotate(Vector3F(0.2F, 0.7F, 0.1F),
		MathF::FMod(static_cast<Float>(System::GetTime()), MathF::TWO_PI));
	transformation.SetRotate(rotate);

	GetRenderer()->ClearBuffers();
	GetRenderer()->PreDraw(mspCamera);
	GetRenderer()->Draw(mspCube, transformation);
	GetRenderer()->PostDraw();
	GetRenderer()->DisplayBackBuffer();
}

//----------------------------------------------------------------------------
void Sample0::OnTerminate()
{
	// Called by the framework before the renderer gets destructed.
	// Perform any additional clean-up here before the application exits.
}
