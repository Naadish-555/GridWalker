#include "Grid.hpp"


void Grid::init(int width, int height, int cellSize) 
{
	if (cellSize == m_cellSize) return; // Don't do work if size hasn't changed

	m_cellSize = cellSize;
	m_cols = (width / m_cellSize) + 1;  // +1 to include the last col in case it was missed in divison
	m_rows = (height / m_cellSize) + 1; // +1 to include the last col in case it was missed in divison

	cells.clear();
	cells.resize(m_cols * m_rows);
}


void Grid::clear()
{
	for (auto& cell : cells)
	{
		cell.clear();
	}
}


void Grid::getNearby(float x, float y, std::vector<int>& result)
{
	result.clear();
	
	int centerCol = static_cast<int>(x / m_cellSize);
	int centerRow = static_cast<int>(y / m_cellSize);

	for (int offsetY = -1; offsetY <= 1; offsetY++)
	{
		for (int offsetX = -1; offsetX <= 1; offsetX++)
		{
			// Calculate Neighbor Column/Row
			int curCol = centerCol + offsetX;
			int curRow = centerRow + offsetY;

			int index = getIndex(curCol, curRow);

			if (index == -1)	continue;

			const auto& bucket = cells[index];
			result.insert(result.end(), bucket.begin(), bucket.end());
			//result.emplace_back(bucket);
		}

	}
}

