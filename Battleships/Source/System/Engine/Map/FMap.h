////////////////////////////////////////////////////////////////////////////////
// Filename: FMap.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FMap_H_
#define _FMap_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////

/////////////
// DEFINES //
/////////////

/*

	=> Tem que ter como adicionar as construções (criar um objeto especifico para isso)
	=> Tem que ter como adicionar props
	=> Tem que ter como gerar unidades (ou spawn points)
	=> Tem que ter como criar regiões com eventos (igual nas construções)
	=> Tem que ter como criar regiões climáticas
	=> Tem que ter como ter funções que indicam onde o jogador está, se está em alto-mar, se está abaixo de neblina, etc etc

	TO-DO:

		- Cria colisão no flipbook (permitir que alguns flipbooks ignorem colisões) e criar funções de callback (ou teste de re-alocação) para indicar colisão
		- Objeto que libera eventos com proximidade
		- Objeto para construções
		- Objeto para o clima
*/

////////////////////////////////////////////////////////////////////////////////
// Class name: FMap
////////////////////////////////////////////////////////////////////////////////
class FMap
{
private:

public:
	FMap();
	FMap(const FMap&);
	~FMap();

	bool Initialize();

private:



};

#endif
