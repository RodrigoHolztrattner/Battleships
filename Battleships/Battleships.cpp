// Battleships.cpp : Defines the entry point for the console application.
//

#include "Source\System\FSystem.h"

/*

	)) TO-DO List:

		=> Os barcos são 3D no jogo
		=> Precisa descobrir se alguma parte do mapa também é 3D (jogar e olhar de perto as ilhas/portos)
		=> Verificar o que pode ser feito com sprite e o que não pode
		=> Desfocar a engine do 2D absoluto e partir para o 2.5D

		- Talvez seja interessante criar uma classe para ser herdada que contenha as funções basicas de Load?, Update, Render e Release?.
		- Criar uma classe (Updateable?) que faz o que foi dito acima, sim, precisamos de uma classe assim, só tem que ver qual categoria ela vai ficar...

		=> Criar as funções de carregamento de textura.

		=> Criar objetos de teste (textura, sprite e ship)
*/

int main()
{
	FSystem systemObject;
	bool bResult;

	// Initialize the system
	bResult = systemObject.Initialize();
	if (!bResult)
	{
		// Error
		return 1;
	}

	// Start the system engine
	systemObject.StartEngine();

	// Shutdown the system
	systemObject.Shutdown();

	return 0;
}

