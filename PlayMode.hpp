#include "Mode.hpp"

#include "Scene.hpp"
#include "Sound.hpp"
#include "script.cpp"

#include <glm/glm.hpp>

#include <vector>
#include <deque>

struct PlayMode : Mode {
	PlayMode();
	virtual ~PlayMode();

	//functions called by main loop:
	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;

	//----- game state -----
// for text:
// struct postexvertext{
// glm::vec3 pos
// vec2 texcoord
// };
// struct{
// 	GLuint text
// 	buffer //tristrip
// 	vao (virtex array object, bind triscript for texture program)

// 	GLsizei count
// 	VLIP_FROM_LOCAL = I
// } tex_ex;
	//example texture drawing:
	struct PosTexVertex {
		glm::vec3 Position;
		glm::vec2 TexCoord;
	};
	static_assert( sizeof(PosTexVertex) == 3*4 + 2*4, "PosTexVertex is packed." );
	struct text {
		GLuint tex = 0; //created at startup
		GLuint tristrip = 0; //vertex buffer (of PosTexVertex)
		GLuint tristrip_for_texture_program = 0; //vertex array object

		GLuint count = 0; //number of vertices in buffer
		glm::mat4 CLIP_FROM_LOCAL = glm::mat4(1.0f); //transform to use when drawing
	} ;
	text tex_example;
	std::vector< text> bkgrd_imgs; 
	std::vector<text> font_texs;

	//input tracking:
	struct Button {
		uint8_t downs = 0;
		uint8_t pressed = 0;
	} one,two,three;

	//local copy of the game scene (so code can change it during gameplay):
	Scene scene;

	//hexapod leg to wobble:
	// Scene::Transform *hip = nullptr;
	// Scene::Transform *upper_leg = nullptr;
	// Scene::Transform *lower_leg = nullptr;
	// glm::quat hip_base_rotation;
	// glm::quat upper_leg_base_rotation;
	// glm::quat lower_leg_base_rotation;
	// float wobble = 0.0f;

	// glm::vec3 get_leg_tip_position();

	//music coming from the tip of the leg (as a demonstration):
	std::shared_ptr< Sound::PlayingSample > leg_tip_loop;
	
	//camera:
	Scene::Camera *camera = nullptr;

	// text
	struct Character {
		unsigned int TextureID;  // ID handle of the glyph texture
		glm::ivec2   Size;       // Size of glyph
		glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
		unsigned int Advance;    // Offset to advance to next glyph
	};
	std::vector<Character> Characters; 
	// unsigned int VAO, VBO;
	void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);

	Script script;
	int currentScene = 0;
	std::string dialogueText="";
	float readtime = 2.0f;

};
