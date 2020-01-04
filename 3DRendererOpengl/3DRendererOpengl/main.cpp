#include "StdAfx.h"

#define STB_IMAGE_IMPLEMENTATION

#include <iostream>

size_t IRenderListener::count = 0;

#include "RenderPipeline.h"
#include "Texture2D.h"
#include "ObjLoader.h"
#include "Object.h"
#include "Camera.h"
#include "PickingTexture.h"
#include "ReferenceGrid.h"
#include "MovableArrows.h"
#include "MaterialLibrary.h"

#include "glfw3.h"
#include "boost/filesystem.hpp"
#include "Skybox.h"

Camera camera;
PickingTexture pickingTexture;
bool isSetMode = false;

void window_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	pickingTexture.Initialize(width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_W:
		{
			camera.ProcessKeyboard(ECameraMovement::FORWARD);
			break;
		}
		case GLFW_KEY_A:
		{
			camera.ProcessKeyboard(ECameraMovement::LEFT);
			break;
		}
		case GLFW_KEY_S:
		{
			camera.ProcessKeyboard(ECameraMovement::BACKWARD);
			break;
		}
		case GLFW_KEY_D:
		{
			camera.ProcessKeyboard(ECameraMovement::RIGHT);
			break;
		}
		case GLFW_KEY_X:
		{
			if (!isSetMode)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				isSetMode = true;
			}
			else
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				isSetMode = false;
			}

			break;
		}
		}
	}
	else if (action == GLFW_RELEASE)
	{
		switch (key)
		{
		case GLFW_KEY_W:
		{
			camera.ProcessKeyboard(ECameraMovement::FORWARD, true);
			break;
		}
		case GLFW_KEY_A:
		{
			camera.ProcessKeyboard(ECameraMovement::LEFT, true);
			break;
		}
		case GLFW_KEY_S:
		{
			camera.ProcessKeyboard(ECameraMovement::BACKWARD, true);
			break;
		}
		case GLFW_KEY_D:
		{
			camera.ProcessKeyboard(ECameraMovement::RIGHT, true);
			break;
		}
		}
	}
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS ||
		glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		camera.ProcessMouseMovement((float)xpos, (float)ypos);
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
		case GLFW_MOUSE_BUTTON_RIGHT:
		{
			double posX, posY;
			glfwGetCursorPos(window, &posX, &posY);
			camera.ProcessMousePosition(static_cast<float>(posX), static_cast<float>(posY));
			break;
		}
		}
	}
}



void RenderCube(Shader& shader, Texture2D& diffuseMap, Texture2D& normalMap)
{
	shader.SetMat4("model", glm::mat4(1.0f));

	shader.SetInt("diffuseMap", 0);
	shader.SetInt("normalMap", 1);
	shader.SetVec3("material.ambientColor", glm::vec3(0.6f));
	shader.SetVec3("material.diffuseColor", glm::vec3(1.0f));
	shader.SetVec3("material.specularColor", glm::vec3(0.8f));
	shader.SetFloat("material.shininess", 512.0f);

	Vertex vertices[] = {
		// bottom
		Vertex { glm::vec3(-1.0f, -1.0f, 1.0f),		glm::vec3(0.0f, -1.0f, 0.0f),	glm::vec2(0.0f, 0.0f), },
		Vertex { glm::vec3(-1.0f, -1.0f, -1.0f),	glm::vec3(0.0f, -1.0f, 0.0f),	glm::vec2(0.0f, 1.0f), },
		Vertex { glm::vec3(1.0f, -1.0f, -1.0f),		glm::vec3(0.0f, -1.0f, 0.0f),	glm::vec2(1.0f, 1.0f), },
		Vertex { glm::vec3(1.0f, -1.0f, 1.0f),		glm::vec3(0.0f, -1.0f, 0.0f),	glm::vec2(1.0f, 0.0f), },

		// right
		Vertex { glm::vec3(1.0f, -1.0f, 1.0f),		glm::vec3(1.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 0.0f), },
		Vertex { glm::vec3(1.0f, 1.0f, 1.0f),		glm::vec3(1.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 1.0f), },
		Vertex { glm::vec3(1.0f, 1.0f, -1.0f),		glm::vec3(1.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 1.0f), },
		Vertex { glm::vec3(1.0f, -1.0f, -1.0f),		glm::vec3(1.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f), },

		// back
		Vertex { glm::vec3(1.0f, -1.0f, -1.0f),		glm::vec3(0.0f, 0.0f, -1.0f),	glm::vec2(0.0f, 0.0f), },
		Vertex { glm::vec3(1.0f, 1.0f, -1.0f),		glm::vec3(0.0f, 0.0f, -1.0f),	glm::vec2(0.0f, 1.0f), },
		Vertex { glm::vec3(-1.0f, 1.0f, -1.0f),		glm::vec3(0.0f, 0.0f, -1.0f),	glm::vec2(1.0f, 1.0f), },
		Vertex { glm::vec3(-1.0f, -1.0f, -1.0f),	glm::vec3(0.0f, 0.0f, -1.0f),	glm::vec2(1.0f, 0.0f), },

		// left
		Vertex { glm::vec3(-1.0f, -1.0f, -1.0f),	glm::vec3(-1.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 0.0f), },
		Vertex { glm::vec3(-1.0f, 1.0f, -1.0f),		glm::vec3(-1.0f, 0.0f, 0.0f),	glm::vec2(0.0f, 1.0f), },
		Vertex { glm::vec3(-1.0f, 1.0f, 1.0f),		glm::vec3(-1.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 1.0f), },
		Vertex { glm::vec3(-1.0f, -1.0f, 1.0f),		glm::vec3(-1.0f, 0.0f, 0.0f),	glm::vec2(1.0f, 0.0f), },

		// front
		Vertex { glm::vec3(-1.0f, -1.0f, 1.0f),		glm::vec3(0.0f, 0.0f, 1.0f),	glm::vec2(0.0f, 0.0f), },
		Vertex { glm::vec3(-1.0f, 1.0f, 1.0f),		glm::vec3(0.0f, 0.0f, 1.0f),	glm::vec2(0.0f, 1.0f), },
		Vertex { glm::vec3(1.0f, 1.0f, 1.0f),		glm::vec3(0.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 1.0f), },
		Vertex { glm::vec3(1.0f, -1.0f, 1.0f),		glm::vec3(0.0f, 0.0f, 1.0f),	glm::vec2(1.0f, 0.0f), },


		// up
		Vertex { glm::vec3(-1.0f, 1.0f, 1.0f),		glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 0.0f), },
		Vertex { glm::vec3(-1.0f, 1.0f, -1.0f),		glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(0.0f, 1.0f), },
		Vertex { glm::vec3(1.0f, 1.0f, -1.0f),		glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 1.0f), },
		Vertex { glm::vec3(1.0f, 1.0f, 1.0f),		glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec2(1.0f, 0.0f), },
	};

	GLushort indices[] = {
		0, 1, 2, 2, 3, 0, 

		4, 5, 6, 6, 7, 4,

		8, 9, 10, 10, 11, 8,

		12, 13, 14, 14, 15, 12,

		16, 17, 18, 18, 19, 16,

		20, 21, 22, 22, 23, 20,
	};

	for (int32_t i = 0; i < sizeof(indices) / sizeof(GLushort); i += 3)
	{
		Vertex& v0 = vertices[indices[i]];
		Vertex& v1 = vertices[indices[i + 1]];
		Vertex& v2 = vertices[indices[i + 2]];

		glm::vec3 deltaPos1 = v1.position - v0.position;
		glm::vec3 deltaPos2 = v2.position - v0.position;

		glm::vec2 deltaUV1 = v1.texCoord - v0.texCoord;
		glm::vec2 deltaUV2 = v2.texCoord - v0.texCoord;

		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
		glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
		glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

		vertices[indices[i]].tangent = tangent;
		vertices[indices[i + 1]].tangent = tangent;
		vertices[indices[i + 2]].tangent = tangent;

		vertices[indices[i]].bitangent = bitangent;
		vertices[indices[i + 1]].bitangent = bitangent;
		vertices[indices[i + 2]].bitangent = bitangent;
	}

	GLuint VAO, VBO, IBO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap.GetHandle());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, normalMap.GetHandle());

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(sizeof(glm::vec3) ));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(sizeof(glm::vec3) * 2 ));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(sizeof(glm::vec3) * 2 + sizeof(glm::vec2)));
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(sizeof(glm::vec3) * 3 + sizeof(glm::vec2)));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, (const void*)0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

int main()
{
	gParams = new Params();

	glfwInit();

	glfwWindowHint(GLFW_SAMPLES, 8);

	MSG(ETypeMessage::Log, "Initilazetion window");

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Render", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	glewInit();

	glEnable(GL_DEPTH_TEST);

	int width, height;
	glfwGetWindowSize(window, &width, &height);

	glViewport(0, 0, width, height);
	pickingTexture.Initialize(width, height);

	gParams->gRenderPipeline = new RenderPipeline();
	Shader commonShader(boost::filesystem::absolute("commonShader.vert").string().c_str(), boost::filesystem::absolute("commonShader.frag").string().c_str());
	Shader pickingShader(boost::filesystem::absolute("pickingShader.vert").string().c_str(), boost::filesystem::absolute("pickingShader.frag").string().c_str());
	Shader boundingBoxShader(boost::filesystem::absolute("boundingBoxShader.vert").string().c_str(), boost::filesystem::absolute("boundingBoxShader.frag").string().c_str());
	Shader referenceGridShader(boost::filesystem::absolute("referenceGridShader.vert").string().c_str(), boost::filesystem::absolute("referenceGridShader.frag").string().c_str());
	Shader movableArrowsShader(boost::filesystem::absolute("movableArrowsShader.vert").string().c_str(), boost::filesystem::absolute("movableArrowsShader.frag").string().c_str());
	Shader skyboxShader(boost::filesystem::absolute("skyboxShader.vert").string().c_str(), boost::filesystem::absolute("skyboxShader.frag").string().c_str());
	BoundingBox boundingBox;
	ReferenceGrid referenceGrid(20, 20);
	MovableArrows movableArrows;
	
	Object model;
	model.SetLoader(new ObjLoader());
	model.Initialize(boost::filesystem::absolute("Models/medieval house.obj").string());
	model.SetBoundingBox(&boundingBox);

	std::chrono::time_point<std::chrono::high_resolution_clock> lastFrameTime;

	Texture2D diffuseMap(boost::filesystem::absolute("Textures/Brick_Wall.jpg").string(), true);
	Texture2D normalMap(boost::filesystem::absolute("Textures/Brick_Wall_Normal.jpg").string(), true);

	CubeTexture cubeTexture({
		boost::filesystem::absolute("Textures/Skybox/lagoon_ft.tga").string(), // front
		boost::filesystem::absolute("Textures/Skybox/lagoon_bk.tga").string(), // back
		boost::filesystem::absolute("Textures/Skybox/lagoon_dn.tga").string(), // down
		boost::filesystem::absolute("Textures/Skybox/lagoon_up.tga").string(), // up
		boost::filesystem::absolute("Textures/Skybox/lagoon_rt.tga").string(), // right
		boost::filesystem::absolute("Textures/Skybox/lagoon_lf.tga").string(), // left
		},
		true);

	Skybox skybox(10.0f, cubeTexture);

	while (!glfwWindowShouldClose(window))
	{
		std::chrono::time_point<std::chrono::high_resolution_clock> currentFrameTime = std::chrono::high_resolution_clock::now();
		int64_t delta = std::chrono::duration_cast<std::chrono::microseconds>(currentFrameTime - lastFrameTime).count();
		lastFrameTime = currentFrameTime;

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.UpdatePosotion(delta / 1000.0f);

		/*pickingShader.Use();
		pickingShader.SetMat4("projection", camera.MakeProjectionMatrix());
		pickingShader.SetMat4("view", camera.MakeViewMatrix());

		pickingTexture.EnableWriting();
		gParams->gRenderPipeline->Render(pickingShader);

		glClear(GL_DEPTH_BUFFER_BIT);

		movableArrows.Render(pickingShader);

		pickingTexture.DisableWriting();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			double posX, posY;
			glfwGetCursorPos(window, &posX, &posY);
			auto pixel = pickingTexture.ReadPixel((size_t)posX, (size_t)(height - posY - 1));
			
			std::cout << pixel.ObjectID << std::endl;

			if (pixel.ObjectID == 2)
			{
				boundingBoxShader.Use();
				boundingBoxShader.SetMat4("projection", camera.MakeProjectionMatrix());
				boundingBoxShader.SetMat4("view", camera.MakeViewMatrix());
				boundingBox.Render(boundingBoxShader);
			}
		}

		commonShader.Use();
		commonShader.SetMat4("projection", camera.MakeProjectionMatrix());
		commonShader.SetMat4("view", camera.MakeViewMatrix());
		commonShader.SetVec3("viewPos", camera.Position());

		gParams->gRenderPipeline->Render(commonShader);

		glClear(GL_DEPTH_BUFFER_BIT);

		movableArrowsShader.Use();
		movableArrowsShader.SetMat4("projection", camera.MakeProjectionMatrix());
		movableArrowsShader.SetMat4("view", camera.MakeViewMatrix());
		movableArrows.Render(movableArrowsShader);*/

		commonShader.Use();
		commonShader.SetMat4("projection", camera.MakeProjectionMatrix());
		commonShader.SetMat4("view", camera.MakeViewMatrix());
		commonShader.SetVec3("viewPos", camera.Position());
		commonShader.SetVec3("lightPos", glm::vec3(0.0f, 0.0f, -5.0f));

		RenderCube(commonShader, diffuseMap, normalMap);
		//model.Draw(commonShader);

		skyboxShader.Use();
		skyboxShader.SetMat4("projection", camera.MakeProjectionMatrix());
		skyboxShader.SetMat4("view", glm::mat4(glm::mat3(camera.MakeViewMatrix())));
		skybox.Draw(skyboxShader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}