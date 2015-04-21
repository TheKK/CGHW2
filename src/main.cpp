#include <cstdlib>
#include <cstdio>
#include <stdexcept>

#include "game.h"

int
main(int argc, char* argv[])
{
	try {
		Game game(argc, argv);

		game.execute();

	} catch (const std::exception& e) {
		fprintf(stderr, "%s\n", e.what());
		fprintf(stderr, "[Main] Program shutdown\n");

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
