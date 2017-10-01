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

	=> Tem que ter como adicionar as constru��es (criar um objeto especifico para isso)
	=> Tem que ter como adicionar props
	=> Tem que ter como gerar unidades (ou spawn points)
	=> Tem que ter como criar regi�es com eventos (igual nas constru��es)
	=> Tem que ter como criar regi�es clim�ticas
	=> Tem que ter como ter fun��es que indicam onde o jogador est�, se est� em alto-mar, se est� abaixo de neblina, etc etc

	TO-DO:

		- Cria colis�o no flipbook (permitir que alguns flipbooks ignorem colis�es) e criar fun��es de callback (ou teste de re-aloca��o) para indicar colis�o
		- Objeto que libera eventos com proximidade
		- Objeto para constru��es
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
