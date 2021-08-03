#include "ISHTest.h"
#include "pch.h"
#include <math.h>



void Matreces::ISHMatrix::InsertRow(std::vector<F32> MatrixRow)
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

F32 Matreces::ISHMatrix::GetElementValue(F32 i, F32 j)
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

void Matreces::ISHMatrix::SetElementValue(F32 i, F32 j, F32 newValue)
{

	for (auto& it_Idx : m_Rows)
	{
		for (auto& it_it_Idx : it_Idx)
		{
			if (it_it_Idx.i == i && it_it_Idx.j == j)
			{
				it_it_Idx.val = newValue;				
			}
		}
	}

}

// TODO calculate the determinant.
F32 Matreces::ISHMatrix::CalculateDeterminant()
{
	using namespace Matreces;

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

Matreces::ISHMatrix* Matreces::ISHMatrix::ComputeMatrixMinor(F32 i , F32 j)
{

	using namespace Matreces;
	ISHMatrix* returnMatrix = new ISHMatrix();

	ASSERT(m_numRows > 0 && m_numColumns > 0);
	if(!(m_numRows > 0 && m_numColumns > 0))
	{
		return returnMatrix;
	}

	if( (m_numColumns != m_numRows) )
	{
		// this is not a quadratic matrix.
		ASSERT(m_numColumns != m_numRows);
		return returnMatrix;
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

Matreces::ISHMatrix* Matreces::ISHMatrix::ComputeTranspose()
{
	using namespace Matreces;
	
	if (!IsQuadratic())
	{
		return nullptr;
	}


	ISHMatrix* returnMatrix = this;

	// Change the i and j of the components of the matrix, then we just compute the new matrix.	
	std::vector<std::vector<MatrixIndex>>l_MatrixRows = returnMatrix->m_Rows;
	std::vector<std::vector<MatrixIndex>> n_rows;
	std::vector<std::vector<MatrixIndex>>::iterator it_Rows =l_MatrixRows.begin();
	

	// compute the new rows

	while( it_Rows != l_MatrixRows.end() )
	{
		std::vector<MatrixIndex>::iterator it_Elements =it_Rows->begin();
		
		while ( it_Elements != it_Rows->end() )
		{
			
			F32 n_i = it_Elements->j;
			F32 n_j = it_Elements->i;
			
			it_Elements->i = n_i;
			it_Elements->j = n_j;

			it_Elements++;
		}

		n_rows.push_back(*it_Rows);
		
		it_Rows++;
	}

	// organize the rows 

	U32 l_RowMaxIdx = returnMatrix->m_numRows;
	U32 l_ColMaxIdx = returnMatrix->m_numColumns;
	std::vector<std::vector<MatrixIndex>>n_OrganizedRows;


	for(U32 Idx = 0; Idx < l_RowMaxIdx; ++Idx)
	{	
		std::vector<MatrixIndex>OrganizedRow;

		for( auto _Idx: n_rows )
		{
			for( auto __Idx :_Idx )
			{
				if ((__Idx).i == 1 + Idx)
				{
					OrganizedRow.push_back(__Idx);
				}
			}
		}
		
		n_OrganizedRows.push_back(OrganizedRow);
	}


	returnMatrix->m_Rows = n_OrganizedRows;

	return returnMatrix;
}

Matreces::ISHMatrix* Matreces::ISHMatrix::ComputeInverse()
{
	ISHMatrix* returnMatrix = nullptr;

	if (!IsQuadratic() || !IsInvertible())
	{
		
		std::cout << "The matrix has no inverse." << std::endl;

		return nullptr;
	}
	return returnMatrix = *(ComputeAdjunt()->ComputeTranspose()) * ((F32)1 / CalculateDeterminant());
}

Matreces::ISHMatrix* Matreces::ISHMatrix::ComputeAdjunt()
{

	using namespace Matreces;


	ISHMatrix* returnMatrix = new ISHMatrix(m_numRows,m_numColumns);


	if( !IsQuadratic() )
	{
		return nullptr;
	}

	for (auto rows : m_Rows)
	{

		for (auto elements : rows)
		{
			
			ISHMatrix* ma = ComputeMatrixMinor((elements).i, elements.j);
			F32 a = ma->CalculateDeterminant();
			F32 i = std::pow(-1, (elements.i + elements.j));
			F32 n_elementVal =  i* a;

			returnMatrix->SetElementValue(elements.i, elements.j,n_elementVal);

		}

	}

	return returnMatrix;
}

bool Matreces::ISHMatrix::IsQuadratic()
{
	return (m_numRows == m_numColumns);
}

bool Matreces::ISHMatrix::IsInvertible()
{
	return this->CalculateDeterminant() > 0;
}



void Matreces::ISHMatrix::ComputeEmptyMatrix(U32 m, U32 n)
{
	

	for( U32 Idx = 0; Idx < m_numColumns; ++Idx )
	{
		std::vector<F32>l_Row;

		for( U32 _Idx = 0;_Idx < m_numRows;++_Idx )
		{
		
			l_Row.push_back(0);

		}

		ComputeRow(l_Row,1+Idx);

	}

}

void Matreces::ISHMatrix::ComputeMatrixFromVector(std::vector<F32> m)
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
					
					this->ComputeRow(l_Row,1+row_Idx);
					l_Row.clear();
					row_Idx++;
					column_Idx = 0;
				}
			}

		}

	 }
}

void Matreces::ISHMatrix::ComputeRow(std::vector<F32> m, U32 row)
{
	using namespace Matreces;

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
			U32 column = 1+columnIdx;

			l_m.push_back(MatrixIndex(row, column, v));

			columnIdx++;
		}

	}
	
	m_Rows.push_back(l_m);

}
