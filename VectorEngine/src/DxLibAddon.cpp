#include "DxLibAddon.hpp"

int DxLibAddon::DrawString(const VECTOR2i pos, const std::string text, const COLOR color, const int size, const bool isCentered)
{
	SetFontSize(size);
	if (isCentered)
	{
		int width = DxLib::GetDrawStringWidth(text.data(), text.length());
		return DxLib::DrawString(pos.x - width / 2, pos.y - size / 2, text.data(), color.rgb);
	}
	else
	{
		return DxLib::DrawString(pos.x, pos.y, text.data(), color.rgb);
	}
}

int DxLibAddon::DrawExtendGraph(const VECTOR2i pos, const VECTOR2i size, const Graph graph, const int transFlag)
{
	return DxLib::DrawExtendGraph(pos.x, pos.y, pos.x + graph.width * size.x, pos.y + graph.height * size.y, graph.graph, transFlag);
}

int DxLibAddon::DrawLine(const VECTOR2i pos1, const VECTOR2i pos2, const COLOR color, const int lineThickness)
{
	return DxLib::DrawLine(pos1.x, pos1.y, pos2.x, pos2.y, color.rgb, lineThickness);
}

int DxLibAddon::DrawLineAA(const VECTOR2i pos1, const VECTOR2i pos2, const COLOR color, const int lineThickness)
{
	return DxLib::DrawLineAA(pos1.x, pos1.y, pos2.x, pos2.y, color.rgb, lineThickness);
}

bool DxLibAddon::doDelay()
{
	uint64_t currentTick = GetNowSysPerformanceCount();
	static uint64_t nextTick = currentTick;
	static double extraTick = 0;

	extraTick += fmod(1000 / (double)FPS, 1);
	nextTick += (1000 / FPS) + (int)extraTick;
	if (currentTick < nextTick) {
		WaitTimer((nextTick + (int)extraTick) - currentTick);
		extraTick -= (int)extraTick;
		return false;
	}
	return true;
}

Graph::Graph() {
	graph = NULL;
	width = 0;
	height = 0;
}

Graph::Graph(const std::string imagePath, const int atlasCountX, const int atlasCountY) {
	this->graph = LoadGraph(imagePath.data());
	InitializeGraph(graph, atlasCountX, atlasCountY);
}


Graph::Graph(const int graph) {
	this->graph = graph;
	InitializeGraph(graph);
}

//Graph::Graph(Graph& graph) {
//	*this = graph;
//}
//
//Graph& Graph::operator=(const Graph rhs) {
//	graph = rhs.graph;
//	bounds = rhs.bounds;
//}

void Graph::InitializeGraph(const int graph, const int atlasCountX, const int atlasCountY)
{
	GetGraphSize(graph, &width, &height);
	width /= atlasCountX;
	height /= atlasCountY;
}
