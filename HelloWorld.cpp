//
// Copyright (c) 2008-2018 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
#include "imgui.h"
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Core/ProcessUtils.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/UI.h>

#include "HelloWorld.h"
#include <Urho3D/DebugNew.h>
// Expands to this example's entry-point
URHO3D_DEFINE_APPLICATION_MAIN(HelloWorld)

HelloWorld::HelloWorld(Context* context) :
    Sample(context)
{
	//_CrtSetBreakAlloc(12310);
}

void HelloWorld::Start()
{
    // Execute base class startup
    //Sample::Start();

    // Create "Hello World" Text
    //CreateText();

    // Finally subscribe to the update event. Note that by subscribing events at this point we have already missed some events
    // like the ScreenMode event sent by the Graphics subsystem when opening the application window. To catch those as well we
    // could subscribe in the constructor instead.
    SubscribeToEvents();

    // Set the mouse mode to use in the sample
    Sample::InitMouseMode(MM_FREE);
	context_->RegisterSubsystem(new UrhoImgui(context_));
}

void HelloWorld::Stop()
{
	Sample::Stop();
}

void HelloWorld::CreateText()
{
    auto* cache = GetSubsystem<ResourceCache>();

    // Construct new Text object
    SharedPtr<Text> helloText(new Text(context_));

    // Set String to display
    helloText->SetText("Hello World from Urho3D!");

    // Set font and text color
    helloText->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 30);
    helloText->SetColor(Color(0.0f, 1.0f, 0.0f));

    // Align Text center-screen
    helloText->SetHorizontalAlignment(HA_CENTER);
    helloText->SetVerticalAlignment(VA_CENTER);

    // Add Text instance to the UI root element
    GetSubsystem<UI>()->GetRoot()->AddChild(helloText);
}

void HelloWorld::SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(HelloWorld, HandleUpdate));
	SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(HelloWorld, HandleKeyDown));
	SubscribeToEvent(E_IMGUI_NEWFRAME, URHO3D_HANDLER(HelloWorld, HandleImGuiNewFrame));
}

void HelloWorld::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    // Do nothing for now, could be extended to eg. animate the display
}

void HelloWorld::HandleKeyDown(StringHash eventType, VariantMap & eventData)
{
}

void HelloWorld::HandleImGuiNewFrame(StringHash eventType, VariantMap & eventData)
{
	// 1. Show a simple window
	// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
	{
		static float f = 0.0f;
		ImGui::Text("Hello, world!");
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

	// imgui's Test window
	//ImGui::ShowTestWindow();

	// Using Urho3D texture with the integration's renderer
	auto cache = GetSubsystem<ResourceCache>();
	auto logoTexture = cache->GetResource<Texture2D>("Textures/LogoLarge.png");
	if (!logoTexture)
		return;

	ImGui::Image((void*)logoTexture, ImVec2((float)logoTexture->GetWidth(), (float)logoTexture->GetHeight()), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
}
