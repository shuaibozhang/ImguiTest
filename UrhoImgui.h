#pragma once

#include "../Core/Object.h"
#include "../Graphics/VertexBuffer.h"
#include "../UI/Cursor.h"
#include "../UI/UIBatch.h"

namespace Urho3D
{
	// imgui frame start event
	URHO3D_EVENT(E_IMGUI_NEWFRAME, imguiNewFrame)
	{
	}

	class URHO3D_API UrhoImgui : public Object
	{
		URHO3D_OBJECT(UrhoImgui, Object);

	public:
		/// Construct.
		explicit UrhoImgui(Context* context);
		/// Destruct.
		~UrhoImgui() override;
	protected:
		bool isActive = false;
		// Used to track if there's already a touch, since imgui doesn't have multi-touch support.
		bool touching = false;
		// The touch ID of the single tracked touch
		int single_touchID;


		static const char* GetClipboardText(void* user_data);
		static void SetClipboardText(void* user_data, const char* text);

		// Call ImGui::NewFrame()
		void HandlePostUpdate(StringHash eventType, VariantMap& eventData);
		// Call ImGui::Render()
		void HandleEndRendering(StringHash eventType, VariantMap& eventData);

		// Input
		void HandleKeyUp(StringHash eventType, VariantMap& eventData);
		void HandleKeyDown(StringHash eventType, VariantMap& eventData);
		void HandleTextInput(StringHash eventType, VariantMap& eventData);
		void HandleTouchBegin(StringHash eventType, VariantMap& eventData);
		void HandleTouchEnd(StringHash eventType, VariantMap& eventData);
		void HandleTouchMove(StringHash eventType, VariantMap& eventData);
	};
}
