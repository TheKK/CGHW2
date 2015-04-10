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

	} catch (std::runtime_error e) {
		fprintf(stderr, "%s\n", e.what());

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
