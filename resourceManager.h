#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include <map>

template <class T>
class ResourceManager
{
public:
	ResourceManager();

	std::shared_ptr<T> aquire(const std::string& resourcePath);
private:
	std::map<std::string, std::weak_ptr<T>> _resources;
};

template <class T>
ResourceManager<T>::ResourceManager()
{
}

template <class T>
std::shared_ptr<T>
ResourceManager<T>::aquire(const std::string& resourcePath)
{
	std::shared_ptr<T> toReturn;

	if (_resources.count(resourcePath) == 1)
		toReturn = _resources[resourcePath].lock();
	else {
		std::string msg = "Create: " + resourcePath;

		toReturn.reset(
			new T(resourcePath),
			[this, resourcePath](T* tPtr)
			{
				std::string msg = "Delete: " + resourcePath;

				delete tPtr;
				this->_resources.erase(resourcePath);
				SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
					    msg.c_str());
			});

		_resources[resourcePath] = toReturn;
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, msg.c_str());
	}

	return toReturn;
}

#endif /* RESOURCE_MANAGER_H */
