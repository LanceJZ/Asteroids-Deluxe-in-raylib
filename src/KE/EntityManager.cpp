#include "EntityManager.h"

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{
}

bool EntityManager::Initialize()
{
	for (auto entity : Entities)
	{
		entity->Initialize();
	}

	for (auto lineModel : LineModels)
	{
		lineModel->Initialize();
	}

	for (auto model3D : Model3Ds)
	{
		model3D->Initialize();
	}

	return false;
}

bool EntityManager::BeginRun()
{

	for (auto model3D : Model3Ds)
	{
		model3D->BeginRun(TheCamera);
	}


	return false;
}

void EntityManager::Input()
{
	for (auto lineModel : LineModels)
	{
		lineModel->Input();
	}

	for (auto model3D : Model3Ds)
	{
		model3D->Input();
	}
}

void EntityManager::Update(float deltaTime)
{
	for (auto entity : Entities)
	{
		entity->Update(deltaTime);
	}

	for (auto lineModel : LineModels)
	{
		lineModel->Update(deltaTime);
	}

	for (auto model3D : Model3Ds)
	{
		model3D->Update(deltaTime);
	}
}

void EntityManager::Draw()
{
	for (auto entity : Entities)
	{
		entity->Draw();
	}

	for (auto lineModel : LineModels)
	{
		lineModel->Draw();
	}

	for (auto model3D : Model3Ds)
	{
		model3D->Draw();
	}
}

void EntityManager::AddEntity(std::shared_ptr<Entity> entity)
{
	Entities.push_back(entity);
}

void EntityManager::AddLineModel(std::shared_ptr<LineModel> model)
{
	LineModels.push_back(model);
}

void EntityManager::AddModel3D(std::shared_ptr<Model3D> model, Camera* camera)
{
	TheCamera = camera;
	Model3Ds.push_back(model);
}

std::shared_ptr<Entity> EntityManager::CreateEntity()
{
	std::shared_ptr<Entity> newEntity = std::make_shared<Entity>();
	Entities.push_back(newEntity);

	return newEntity;
}

std::shared_ptr<LineModel> EntityManager::CreateLineModel()
{
	std::shared_ptr<LineModel> newLineModel = std::make_shared<LineModel>();
	LineModels.push_back(newLineModel);

	return newLineModel;
}

std::shared_ptr<Model3D> EntityManager::CreateModel3D()
{
	std::shared_ptr<Model3D> newModel3D = std::make_shared<Model3D>();
	Model3Ds.push_back(newModel3D);

	return newModel3D;
}
