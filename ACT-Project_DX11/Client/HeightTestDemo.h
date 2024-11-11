#pragma once


class HeightTestDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

	void CreatePlayer();

private:
	shared_ptr<Shader> _shader;
	shared_ptr<Shader> _renderShader;
};