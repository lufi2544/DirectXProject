#pragma once
#include <iostream>
#include <ostream>
#include <functional>
#include <assert.h>
#include <cassert>
#include <intrin.h>
#include <memory>
#include <vector>


// define some inline assembly that causes a break
// into the debugger -- this will be different on each
// target CPU
#define debugBreak()_asm{ int 3 }

#if _DEBUG

	#define SLOW_ASSERT(exp) \
	if(exp){} \
	else{\
	reportSLOWAssertionFailure(#exp , __FILE__,__LINE__);\
	debugBreak();\
	}

	// this is a function for the slow assertions. This is meant to be the assertion that explains the problem more in depth. ( creation of a window for example ).
	inline void reportSLOWAssertionFailure( const char* _exp, const char* _file , int _line ){ std::cout << "Expression " << _exp << " has a slow assertion in the file -> " << _file << " .Line ->  " << _line; };

#endif // _DEBUG


// check the expression and fail if it is false
#define ASSERT(expr) \
	\
	if(expr){ } \
	\
	else \
	{ \
	reportAssertionFailure(#expr, \
	\
	__FILE__, __LINE__); \
	\
	debugBreak();\
	}

inline void reportAssertionFailure(std::string _exp , std::string _file , int _line){ std::cout <<"Expression " << _exp <<" has an assertion in the file -> "<< _file << " .Line ->  " << _line;};

// Another Assert that we have to declare is the compile time assertion that checks for the bytes that a struct may have for example
// we can implement this by different methods



#define _ASSERT_GLUE_(a,b) a ## b
#define ASSERT_GLUE(a,b) _ASSERT_GLUE_(a,b)

//Method 1

/*
#define STATIC_ASSERT(expr) \
	enum{ \
		ASSERT_GLUE(g_static_assertion_fail,__LINE__) \
		= 1/(int)( !!exp );\
	}
	*/

// Method 2 We just define the true case for the class, so when the expression is false, the compiler will advise us.

 template<bool>class TStaticAssert;
 template<>class	 TStaticAssert<true>{};

 #define STATIC_ASSERT(expr) \
	 enum{ \
		ASSERT_GLUE(g_static_assertion_fail,__LINE__) \
		= sizeof(TStaticAssert<!!(expr)>)\
	}

struct st
{
	unsigned int x, y, z, w;
	
};

// Whatever tests classes, structs or functionalities that will be tested will be included here.
namespace TestField
{

	namespace Exception
	{

		struct ExceptionTest
		{

			void RunTest()
			{
	
					int a, b;
					b = 3;

					std::cin >> a;

					SLOW_ASSERT(a > 0);

			}

		};
	};

	namespace Lambda
	{
	
		class LamdaTest
		{
			public:

			std::function<int(int)>AddNumbers_Lambda(int a)
			{
			
				return[a](int b)
				{

					return a+b;

				};
			
			};

			//Pointer to a function

			// Returns void, is called " function " and takes 2 parameters.
			void ( *function )( int,bool );



			static std::function<void(int,st)> TestFunction()
			{

				st myStruct;


				return [&myStruct](int value, st MyStruct)
				{

					std::cout << " Prechange value: " << value << std::endl;
					value = 6;

					std::cout << " The value is: " << value << std::endl;

					myStruct.x = 1;
					MyStruct.y = 2;
					MyStruct.z = 3;
					MyStruct.w = 4;

					std::cout << " The struct values are: " << MyStruct.x << " , " << MyStruct.y << " , " << MyStruct.z << std::endl;
				};



				auto lam = [&myStruct](int a, float b, bool boo, st _st)
				{

					_st.x = 33;

					std::cout << _st.x << std::endl;
					/*	std::cout << my.y << std::endl;*/

					std::cout << a << "  " << b << "  " << boo << " , " << _st.x << " , " << _st.y << " , " << _st.z << std::endl;

					return false;
					
				};

			}
		
		};

	}

	namespace Enums
	{
		enum ETest
		{

			redcolor = 1,
			bluecolor = 33,
			yellowcolor = 2,
			greencolor
		};

	};


	namespace Matreces
	{

		struct MatrixIndex
		{
			MatrixIndex()
			{
				i = 1;
				j = 1;
				val = 0;

			};
	
			MatrixIndex(F32 _i, F32 _j, F32 _val):i(_i),
			j(_j),
			val(_val)
			{}

			F32		i;
			F32		j;
			F32	  val;
		};

		struct ISHMatrix
		{
			
			ISHMatrix()
			{
			
			};

			ISHMatrix(U32 m , U32 n):
			m_numRows(m),
			m_numColumns(n)
			{
				ComputeEmptyMatrix(m,n);
			};

			ISHMatrix( U32 _Rows, U32 _Columns, std::vector<F32> members ):
			m_numColumns(_Columns),
			m_numRows(_Rows)
			{	
				ComputeMatrixFromVector(members);
			};

			// Columns
			U32 m_numColumns = 0;

			//Rows
			U32 m_numRows = 0;
			std::vector<std::vector<Matreces::MatrixIndex>> m_Rows;


 			virtual F32		   CalculateDeterminant();
			virtual ISHMatrix* ComputeMatrixMinor(F32 i, F32 j);
 			virtual ISHMatrix* ComputeTranspose();
 			virtual ISHMatrix* ComputeInverse ();	
			virtual ISHMatrix* ComputeAdjunt();
			bool			   IsQuadratic();
			bool			   IsInvertible();


			void InsertRow(std::vector<F32>MatrixRow);

			F32 GetElementValue(F32 i , F32 j);
			void SetElementValue (F32 i, F32 j, F32 newValue);

			private:

			// Helper function for constructing a new matrix with a certain m rows and n columns
			void  ComputeEmptyMatrix(U32 m, U32 n);

			//  Helper function that creates a matrix ( constructor ).
			void ComputeMatrixFromVector(std::vector<F32> m);

			// this is a helper function for a constructor of the Matrix.
			// The constructor will Store the given @row with the @m values. 
			void ComputeRow(std::vector<F32> m ,U32 row);

			inline ISHMatrix* operator * (F32 num )
			{
				for(auto& rows :m_Rows)
				{
					for(auto& elements : rows)
					{

						elements.val *= num;

					}
				}
				
				return this;
			}
			

		};
	};
};

