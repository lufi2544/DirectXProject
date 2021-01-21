// Ishak.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <ostream>
#include <array>
#include <vector>
#include "pch.h"
#include <functional>
#include <cstdarg>
#include "ISHTest.h"


using namespace DirectX;
namespace DX11 = DirectX;

struct EA
{
	int a, b;

};


std::ostream& operator << ( std::ostream& os , DX11::FXMVECTOR v  )
{

    DX11::XMFLOAT3 dest;
    DX11::XMStoreFloat3(&dest , v);

    os << "( " << dest.x << " , "<< dest.y << " , " << dest.z << " )." << std::endl;

    return os;
}



std::ostream& operator<< (std::ostream& os, EA st)
{

	os << " a: " << st.a << " b: " << st.b << std::endl;


	return os;
}


std::ostream& operator << (std::ostream& os, TestField::Matreces::ISHMatrix matrix)
{


	F32 u = 1;
	std::vector<std::vector<TestField::Matreces::MatrixIndex>>::iterator it_MatrixRows = matrix.m_Rows.begin();
	
	while (it_MatrixRows != matrix.m_Rows.end())
	{
		std::vector<TestField::Matreces::MatrixIndex>::iterator it_it_MatrixRows = (*it_MatrixRows).begin();

		while( it_it_MatrixRows != (*it_MatrixRows).end() )
		{

			if (it_it_MatrixRows->i != u)
			{
				u = it_it_MatrixRows->i;
				std::cout << std::endl;

			}
			
			std::cout << it_it_MatrixRows->val << "  ";

			it_it_MatrixRows++;
		}


		it_MatrixRows++;
	}


	return os;
};



namespace GraphicsFunctions
{ 
	float GetAngle3Vectors(DX11::XMVECTOR v1, DX11::XMVECTOR v2)
	{

		float fReturnAngle = 0.0f;
		DX11::XMVECTOR vReturn = DX11::XMVectorSet(0, 0, 0, 0);

		DX11::XMVECTOR vDotProduct = DX11::XMVector3Dot(v1, v2);
		XMFLOAT3 fDotProduct;
		float Dot;

		XMStoreFloat3(&fDotProduct, vDotProduct);

		Dot = fDotProduct.x;

		DX11::XMVECTOR v1Lenght = DX11::XMVector3Length(v1);
		DX11::XMVECTOR v2Lenght = DX11::XMVector3Length(v2);

		XMFLOAT3 fv1Lenght;
		XMFLOAT3 fv2Lenght;

		XMStoreFloat3(&fv1Lenght, v1Lenght);
		XMStoreFloat3(&fv2Lenght, v2Lenght);

		float f1 = fv1Lenght.x;
		float f2 = fv2Lenght.x;

		float cosAlph = (Dot / (f1 * f2));

		float AcosAlph = DX11::XMScalarACos(cosAlph);

		fReturnAngle = DX11::XMConvertToDegrees(AcosAlph);


		return fReturnAngle;
	};
};



struct Example
{

	U32 m_a;
	U16 m_b;
	U32 m_c;

};

struct Stream 
{
	U32 st_a;
	U32 st_b;
	U16 st_c;
};

inline U32 swapU32(U32 value)
{
	return	((value & 0x000000FF) << 24
		|	((value & 0x0000FF00) << 8)
		|	((value & 0x00FF0000) >> 8)
		|	((value & 0xFF000000) >> 24));
}

inline U16 swapU16(U16 value)
{
	return ((value & 0x00FF) << 8)
		|  ((value & 0xFF00) >> 8);
};

void writeExampleStruct( Example& ex, Stream& stream )
{
	stream.st_a = swapU32(ex.m_a);
	stream.st_b = swapU32(ex.m_b);
	stream.st_c = swapU16(ex.m_c);
}

struct Son;
struct Daughter;

struct Mother
{

	std::shared_ptr<Son> p_son;
	std::shared_ptr<Daughter>p_daughter;

	public:

	void SetSon(std::weak_ptr<Son> son)
	{
		p_son = son.lock();
	}

	void SetDaughter(std::weak_ptr<Daughter> daughter)
	{
		p_daughter = daughter.lock();
	}

	~Mother()
	{
		std::cout << " Destroying Mother. " << std::endl;
	}

};

struct Son
{
	std::weak_ptr<const Mother>m_pMother;
public:

	Son(std::shared_ptr<Mother>mother)
		:m_pMother(mother)
	{};

	~Son()
	{
		std::cout << "Destroying Son." << std::endl;
	};
};

struct Daughter
{
	std::weak_ptr<const Mother>m_pMother;

public:

	Daughter(std::shared_ptr<Mother>mother)
		:m_pMother(mother)
	{};

	~Daughter()
	{
		std::cout << "Destroying Daughter." << std::endl;
	};
};






int main()
{
    
	U32 a = 0x00000012;



	//a = swapU32(a);


		U32 b = ((a & 0x000000FF) << 24
 			|	((a & 0x0000FF00) << 8 )
			|	((a & 0x00FF0000) >> 8 )
			|	((a & 0xFF000000) >> 24)	
 			);

	bool b1 = (a & 0x000000FF);
	bool b2 = (a & 0x0000FF00);
	bool b3 = (a & 0x00FF0000);
	bool b4 = (a & 0xFF000000);

	int ab = 0x000000FF;

	//std::cout << "first bit: " << 0x0000FF00 << std::endl;


	if (b1)
	{
		int d =0;
	}
 			
	if(b2)
	{
		int f = a;
	}

	if(b3)
	{
		int a = 3;
	}

	if(b4)
	{
		int g = 4;
	}


	std::vector<F32> vec = { 2,2,2,
							 3,3,3,
							 -1,3,-4 };



	TestField::Matreces::ISHMatrix m = TestField::Matreces::ISHMatrix(3,3,vec) ;



	TestField::Matreces::ISHMatrix* m_minor = m.ComputeMatrixMinor(2,2);

	std::cout << m << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;


	std::cout << *m_minor << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;

	std ::cout << "The transpose of the matrix is : "<< std::endl;

	std::cout << *(m.ComputeTranspose()) << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "The inverse of the matrix is : " << std::endl;

	TestField::Matreces::ISHMatrix* inverse = (m.ComputeInverse());

	if( m.IsInvertible() )
	{

		std::cout << *(inverse) << std::endl;

	}

	

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "The determinant is: " << m.CalculateDeterminant()<< std::endl;

// 
// 	std::shared_ptr< Mother> mother    = std::shared_ptr<Mother>(new Mother) ;
// 	std::shared_ptr<Son>son			   = std::shared_ptr<Son>(new Son(mother));
// 	std::shared_ptr<Daughter> daughter = std::shared_ptr<Daughter>(new Daughter(mother));
// 
// 	mother->SetDaughter(daughter);
// 	mother->SetSon(son);
// 
// 	int asdfasdf = 0;


//     if( !DX11::XMVerifyCPUSupport() )
//     
//     {
//         std::cout << " xnamath is not supported! ( Graphics card base error ) upgrade you pc please. xD "  <<std::endl;
//         return 0;
//     }
//        
// 		std::array<int,4> arr = {};
// 		int i = 0;
// 		std::vector<int>ho= {};
// 
//         XMVECTOR f = XMVectorSet( 3.0f , 4.0f , 5.0f , 0.0f );
//         XMVECTOR g = XMVectorSet( 10.0 , 0.0f , 0.0f , 0.0f );
//         XMVECTOR h = XMVectorSet( 1.0f , 4.0f , 1.0f , 0.0f );
//         XMVECTOR j = XMVectorSet( 0.0f , 0.0f , 0.0f , 0.0f );
// 
// 		ho.push_back(3);
// 		
//         XMVECTOR a = f + g;
//         XMVECTOR b =  XMVector3Dot( f , f );
// 
// 
// 		ho.push_back(2);
// 
// 		int al = 3;
// 
// 		ho.push_back(0);
// 
// 		int s = 0;
// 
// 		for ( int i = 0; i < 4;i++ )
// 		{
// 
// 			++s;	
// 			
// 		
// 
// 		}
// 		
// 
// 
//         std::cout << " Vector a :  " << f << std::endl;
//         std::cout << " Vector b :  " << g << std::endl;
//         std::cout << " angle between the vectors is :  "<< GraphicsFunctions::GetAngle3Vectors(f,g) << std::endl;
//         

}

// Ejecutar programa: Ctrl + F5 o meenú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
