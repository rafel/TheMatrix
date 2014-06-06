#ifndef WINDOW_H
#define WINDOW_H
#define HIDE_MOUSE

#include <string>

#include <glm/glm.hpp>

class Window
{
	private:
		int width;
		int height;
		void initialize(int, int) const;
		void releaseResources() const;

		std::string title;
	public:
		Window();
		~Window();
		void show();
		void update();
		bool windowVisible();
		int getWidth() const;
		int getHeight() const;
		glm::mat4 getProjecionMatrix();
		std::string getTitle() const;
};

#endif
