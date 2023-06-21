#pragma once
#include <memory>
#include <vector>
#include "Entity.h"
#include "LineModel.h"
#include "Model3D.h"

class EntityManager : Common
{
public:
	EntityManager();
	virtual ~EntityManager();

	bool Initialize();
	bool BeginRun();

	void Input();
	void Update(float deltaTime);
	void Draw();

	void AddEntity(std::shared_ptr<Entity> entity);
	void AddLineModel(std::shared_ptr<LineModel> model);
	void AddModel3D(std::shared_ptr<Model3D> model, Camera *camera);

	std::shared_ptr<Entity> CreateEntity();
	std::shared_ptr<LineModel> CreateLineModel();
	std::shared_ptr<Model3D> CreateModel3D();

	std::vector<std::shared_ptr<Entity>> Entities;
	std::vector<std::shared_ptr<LineModel>> LineModels;
	std::vector<std::shared_ptr<Model3D>> Model3Ds;

private:
	Camera* TheCamera;
};

