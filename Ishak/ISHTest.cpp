#include "ISHTest.h"
#include <math.h>



void TestField::Matreces::ISHMatrix::InsertRow(std::vector<F32> MatrixRow)
{
	
	if (m_numRows > 0)
	{
		if (MatrixRow.size() < m_numColumns)
		{
			F32 diff = m_numColumns - MatrixRow.size();
			// the matrix is not quadratic, add 0 in the positions that are blank.
			for(F32 Idx = 0; Idx < diff; ++ Idx)
			{
				MatrixRow.push_back(0);
			}
		}else if( MatrixRow.size() > m_numColumns )
		{
			// the matrix would not be quadratic.
			ASSERT(MatrixRow.size() > m_numColumns);
			return;
		}
		
	}

// check if the matrix is quadratic.

	if (MatrixRow.size() == 0)
	{
		ASSERT(MatrixRow.size() != 0)
		return;
	}

	F32 RowIdx;
	m_numRows == 0 ? m_numRows = 1 : m_numRows++;
	RowIdx = m_numRows;

	std::vector<F32>::iterator it_rows = MatrixRow.begin();
	F32 Idx = 0;

	// Raw Rows to compute
	std::vector<Matreces::MatrixIndex> l_RawRows;

	while (it_rows != MatrixRow.end())
	{
		F32 i,j;

		i = RowIdx;
		j = Idx;
		j++;

		l_RawRows.push_back((Matreces::MatrixIndex(i, j , *it_rows)));

		it_rows++;
		Idx++;
	}

	if (m_numRows == 1)
	{
		m_numColumns = l_RawRows.size();
	}

	m_Rows.push_back(l_RawRows);
 
}

F32 TestField::Matreces::ISHMatrix::GetElementValue(F32 i, F32 j)
{

	F32 r = 0;

	for(auto it_Idx : m_Rows)
	{
		for( auto it_it_Idx : it_Idx )
		{
			if (it_it_Idx.i == i && it_it_Idx.j == j)
			{
				return it_it_Idx.val;
			}
		}	
	}

	return r; 
}

// TODO calculate the determinant.
F32 TestField::Matreces::ISHMatrix::CalculateDeterminant()
{
	using namespace TestField::Matreces;

		F32 det = 0;

	 if ((m_numRows == 1) && (m_numColumns == 1))
	 {
		 F32 r = GetElementValue(1,1);
		return r;
	 }

	 
	 for( auto it_mIdx : m_Rows )
	 {
	

		for( auto it_it_mIdx : it_mIdx )
		{

			if(it_it_mIdx.i == 2)
			{
				return det;
			}

			det += it_it_mIdx.val * (pow(-1, (1 + it_it_mIdx.j))) * ComputeMatrixMinor(it_it_mIdx.i, it_it_mIdx.j)->CalculateDeterminant();

		}

	 }

	 return det;
}

TestField::Matreces::ISHMatrix* TestField::Matreces::ISHMatrix::ComputeMatrixMinor(F32 i , F32 j)
{

	using namespace TestField::Matreces;
	ISHMatrix* returnMatrix = new ISHMatrix();

	ASSERT(m_numRows > 0 && m_numColumns > 0);
	if(!(m_numRows > 0 && m_numColumns > 0))
	{
		return;
	}

	if( (m_numColumns != m_numRows) )
	{
		// this is not a quadratic matrix.
		ASSERT(m_numColumns != m_numRows);
		return;
										 // || m_numColumns == 1
	}else if( (m_numColumns == m_numRows) && (m_numRows == 1) )
	{

		std::vector<F32>l_RowVals;
		l_RowVals.push_back(GetElementValue(1,1));
		returnMatrix->InsertRow(l_RowVals);

		return returnMatrix;
	}

	for (auto it_Idx : m_Rows)
	{
		MatrixIndex l_MI = MatrixIndex();

		for(auto it_it_Idx : it_Idx)
		{
			if (it_it_Idx.j == j && it_it_Idx.i == i )
			{
				l_MI = it_it_Idx;


				for(auto it2_Idx : m_Rows)
				{
				
					std::vector<F32>l_RowVals;

					for(auto it2_it_Idx :it2_Idx )
					{
						
						if( it2_it_Idx.i != l_MI.i && it2_it_Idx.j != l_MI.j  )
						{
							l_RowVals.push_back( it2_it_Idx.val );
						}

					}

					if( l_RowVals.size() > 0 )
					{
						returnMatrix->InsertRow(l_RowVals);
					}

					
				}

			}

		}

	}

	return returnMatrix;
}

void TestField::Matreces::ISHMatrix::ComputeMatrix(std::vector<F32> m)
{
	
	 std::vector<F32>l_Row;
	 U32 row_Idx = 0;
	 U32 column_Idx = 0;

	 for( auto Idx: m )
	 {
		
		if( row_Idx < m_numRows )
		{
			if(column_Idx < m_numColumns)
			{
				l_Row.push_back(Idx);
				column_Idx++;

				if(column_Idx >= m_numColumns)
				{
					U32 row = row_Idx + 1;
					
					this->ComputeRow(l_Row,row);
					l_Row.clear();
					row_Idx++;
					column_Idx = 0;
				}
			}

		}

	 }
}

void TestField::Matreces::ISHMatrix::ComputeRow(std::vector<F32> m, U32 row)
{
	using namespace TestField::Matreces;

	std::vector<MatrixIndex>l_m;
	U32 columnIdx = 0;

	// The rows or the columns have to be already initialized.
	ASSERT(m_numColumns != 0);
	ASSERT(m_numRows != 0);

	if( m_numColumns == 0 || m_numRows == 0 )
	{
		return;
	}

	for (auto v : m)
	{
		if( columnIdx < m_numColumns )
		{
			U32 column = columnIdx + 1;

			l_m.push_back(MatrixIndex(row, column, v));

			columnIdx++;
		}

	}
	
	m_Rows.push_back(l_m);

}
