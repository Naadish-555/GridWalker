#pragma once
#include <vector>

class Grid
{

	int m_cellSize;										//Must be >= Vision Radius
	int m_rows;
	int m_cols;
	std::vector<std::vector<int>> cells;				//vector for storing ids of boids within the grid
	

public:
	
	//.cpp functions

	void init(int width, int height, int cellSize);
	void clear();										//Wipe the grid clean at the start of every frame
	void getNearby(float x, float y, std::vector<int>& result);		//Return a list of all boid IDs in the relevant cells


	//.hpp functions

	Grid() : m_rows(0), m_cols(0), m_cellSize(0) {}

	Grid(int width, int height, int cellSize)
	{
		init(width, height, cellSize);
	}


	int rows() const
	{
		return m_rows;
	}

	int columns() const
	{
		return m_cols;
	}

	int cellsize() const
	{
		return m_cellSize;
	}


	int getIndex(float x, float y)
	{
		int posX = static_cast<int>(x / m_cellSize);
		int posY = static_cast<int>(y / m_cellSize);

		if (posX < 0 || posX >= m_cols || posY < 0 || posY >= m_rows)	return -1;	//out of grid bounds

		return  (posY * m_cols) + posX;
	}

	int getIndex(int x, int y)
	{

		if (x < 0 || x >= m_cols || y < 0 || y >= m_rows)	return -1;	//out of grid bounds

		return (y * m_cols) + x;
	}

	void add(int boidId, float x, float y)					// Put a boid ID into the correct cell
	{
		int index = getIndex(x, y);
		if (index != -1)
			cells[index].emplace_back(boidId);
	}




};