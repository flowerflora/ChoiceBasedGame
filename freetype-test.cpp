#include <ft2build.h>
#include FT_FREETYPE_H

#include <hb.h>
#include <hb-ft.h>

#include <iostream>

#include "TextureProgram.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <glm/glm.hpp>

	#define FONT_SIZE 36
	#define MARGIN (FONT_SIZE * .5)
//This file exists to check that programs that use freetype / harfbuzz link properly in this base code.
//You probably shouldn't be looking here to learn to use either library.
struct Character {
	unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};


int main(int argc, char **argv) {
	const char *fontfile;
	// const char *text;

	if (argc < 3)
	{
		fprintf (stderr, "usage: hello-harfbuzz font-file.ttf text\n");
		exit (1);
	}

	fontfile = argv[1];
	// text = argv[2];

	/* Initialize FreeType and create FreeType font face. */
	FT_Library library;;
	FT_Face ft_face;
	FT_Error ft_error;

	if ((ft_error = FT_Init_FreeType( &library )))
		abort();
	if ((ft_error = FT_New_Face (library, fontfile, 0, &ft_face))) //0 if there is only one face in the font file
		abort();
	if ((ft_error = FT_Set_Char_Size (ft_face, FONT_SIZE*64, FONT_SIZE*64, 0, 0))) //horizontal + vertical resolution -- default 72dpi
		abort();

	// want to use ft to create our text
	// code based on : https://learnopengl.com/In-Practice/Text-Rendering
	// also uses https://freetype.org/freetype2/docs/tutorial/step1.html
	// maybe have the character textures created and then load to binary -- easier to use in playmode
	// size_t num_chars = strlen(text);
	std::vector<Character> Characters;
	// for (size_t n = 0; n < num_chars; n++ ){
	printf("done!\n");
	for (unsigned char c = 0; c < 128; c++){
		FT_UInt  glyph_index;
		/* retrieve glyph index from character code */
		glyph_index = FT_Get_Char_Index(ft_face, c );

		/* load glyph image into the slot (erase previous one) */
		if((ft_error = FT_Load_Glyph(ft_face, glyph_index, FT_LOAD_DEFAULT )))
			continue;  /* ignore errors */

		/* convert to an anti-aliased bitmap */
		if((ft_error = FT_Render_Glyph(ft_face->glyph, FT_RENDER_MODE_NORMAL ))) 
			continue;

		// printf("character %c, bitmap: %d",c,ft_face->glyph->bitmap);
		if (FT_Load_Char(ft_face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}

		std::cout<<(char)c<< "idk man "<<ft_face->glyph->bitmap.buffer<< std::endl;// load first 128 characters of ASCII set
	
		// generate texture
		GLuint texture;
			printf("check\n");
		//-------- texture example initialization ----------
		glGenTextures(1, &texture);
		{ //upload texture data:

			//load texture data as RGBA from a file:
			printf("check\n");
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ft_face->glyph->bitmap.width, ft_face->glyph->bitmap.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, ft_face->glyph->bitmap.buffer);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glGenerateMipmap(GL_TEXTURE_2D);
			// glBindTexture(GL_TEXTURE_2D, 0);
		}


		// glGenTextures(1, &texture);
		// glBindTexture(GL_TEXTURE_2D, texture);
		// // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
		// glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, ft_face->glyph->bitmap.width, ft_face->glyph->bitmap.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, ft_face->glyph->bitmap.buffer);
		// // set texture options
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// now store character for later use
		Character character = {
			texture,
			glm::ivec2(ft_face->glyph->bitmap.width, ft_face->glyph->bitmap.rows),
			glm::ivec2(ft_face->glyph->bitmap_left, ft_face->glyph->bitmap_top),
			static_cast<unsigned int>(ft_face->glyph->advance.x)
		};
		Characters.emplace_back(character);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	
	// lets try exporting this?
	// configure VAO/VBO for texture quads
    // -----------------------------------

	// // create name for vertex buffer:
	// GLuint tristrip;
	// glGenBuffers(1, &tristrip);
	// //(will upload data later)

	// GLuint textristrip;

	// { //set up vertex array:
	// 	glGenVertexArrays(1, &textristrip);
	// 	glBindVertexArray(textristrip);
	// 	glBindBuffer(GL_ARRAY_BUFFER, tristrip);

	// 	glVertexAttribPointer( texture_program->Position_vec4, 3, GL_FLOAT, GL_FALSE, sizeof(PosTexVertex), (GLbyte *)0 + offsetof(struct PosTexVertex , Position) );
	// 	glEnableVertexAttribArray( texture_program->Position_vec4 );

	// 	glVertexAttribPointer( texture_program->TexCoord_vec2, 2, GL_FLOAT, GL_FALSE, sizeof(PosTexVertex), (GLbyte *)0 + offsetof(struct PosTexVertex , TexCoord) );
	// 	glEnableVertexAttribArray( texture_program->TexCoord_vec2 );

	// 	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// 	glBindVertexArray(0);
	// }

		
    // glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &VBO);
    // glBindVertexArray(VAO);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);
	// /* Create hb-ft font. */
	// // how does hb draw ...?
	// hb_font_t *hb_font;
	// hb_font = hb_ft_font_create (ft_face, NULL); // destroy function

	// /* Create hb-buffer and populate. */
	// hb_buffer_t *hb_buffer;
	// hb_buffer = hb_buffer_create (); //default vals
	// hb_buffer_add_utf8 (hb_buffer, text, -1, 0, -1); // null-terminated, 1st char offset, whole text
	// hb_buffer_guess_segment_properties (hb_buffer); //Sets unset buffer segment based on buffer contents

	// /* Shape it! */
	// hb_shape (hb_font, hb_buffer, NULL, 0); //Shapes buffer using font turning its Unicode char content to positioned glyph

	// /* Get glyph information and positions out of the buffer. */
	// unsigned int len = hb_buffer_get_length (hb_buffer);
	// hb_glyph_info_t *info = hb_buffer_get_glyph_infos (hb_buffer, NULL); // NULL pointer to length of out, Returns buffer glyph information array
	// hb_glyph_position_t *pos = hb_buffer_get_glyph_positions (hb_buffer, NULL); //Returns buffer glyph position array

	// /* Print them out as is. */
	// printf ("Raw buffer contents:\n");
	// for (unsigned int i = 0; i < len; i++)
	// {
	// 	hb_codepoint_t gid   = info[i].codepoint; //glyph id
	// 	unsigned int cluster = info[i].cluster;
	// 	double x_advance = pos[i].x_advance / 64.; //divide by 64 cus we multiplied earlier?
	// 	double y_advance = pos[i].y_advance / 64.;
	// 	double x_offset  = pos[i].x_offset / 64.;
	// 	double y_offset  = pos[i].y_offset / 64.;

	// 	char glyphname[32];
	// 	hb_font_get_glyph_name (hb_font, gid, glyphname, sizeof (glyphname)); //Fetches the glyph-name string for a glyph ID in the specified font

	// 	printf ("glyph='%s'	cluster=%d	advance=(%g,%g)	offset=(%g,%g)\n",
	// 			glyphname, cluster, x_advance, y_advance, x_offset, y_offset);
	// }

	// printf ("Converted to absolute positions:\n"); //uses offset + advance(s)
	// /* And converted to absolute positions. */
	// {
	// 	double current_x = 0;
	// 	double current_y = 0;
	// 	for (unsigned int i = 0; i < len; i++)
	// 	{
	// 	hb_codepoint_t gid   = info[i].codepoint;
	// 	unsigned int cluster = info[i].cluster;
	// 	double x_position = current_x + pos[i].x_offset / 64.;
	// 	double y_position = current_y + pos[i].y_offset / 64.;


	// 	char glyphname[32];
	// 	hb_font_get_glyph_name (hb_font, gid, glyphname, sizeof (glyphname));

	// 	printf ("glyph='%s'	cluster=%d	position=(%g,%g)\n",
	// 		glyphname, cluster, x_position, y_position);
		

	// 	current_x += pos[i].x_advance / 64.;
	// 	current_y += pos[i].y_advance / 64.;
	// 	}
	// }

	// // /* Draw, using cairo. */
	// // // cairo is apparently a libaray not a font... lol
	// // // double width = 2 * MARGIN;
	// // // double height = 2 * MARGIN;
	// // // for (unsigned int i = 0; i < len; i++)
	// // // {
	// // // 	width  += pos[i].x_advance / 64.;
	// // // 	height -= pos[i].y_advance / 64.;
	// // // }
	// // // if (HB_DIRECTION_IS_HORIZONTAL (hb_buffer_get_direction(hb_buffer)))
	// // // 	height += FONT_SIZE;
	// // // else
	// // // 	width  += FONT_SIZE;

	// // // /* Set up cairo surface. */
	// // // cairo_surface_t *cairo_surface;
	// // // cairo_surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32,
	// // // 						ceil(width),
	// // // 						ceil(height));
	// // // cairo_t *cr;
	// // // cr = cairo_create (cairo_surface);
	// // // cairo_set_source_rgba (cr, 1., 1., 1., 1.);
	// // // cairo_paint (cr);
	// // // cairo_set_source_rgba (cr, 0., 0., 0., 1.);
	// // // cairo_translate (cr, MARGIN, MARGIN);

	// // // /* Set up cairo font face. */
	// // // cairo_font_face_t *cairo_face;
	// // // cairo_face = cairo_ft_font_face_create_for_ft_face (ft_face, 0);
	// // // cairo_set_font_face (cr, cairo_face);
	// // // cairo_set_font_size (cr, FONT_SIZE);

	// // // /* Set up baseline. */
	// // // if (HB_DIRECTION_IS_HORIZONTAL (hb_buffer_get_direction(hb_buffer)))
	// // // {
	// // // 	cairo_font_extents_t font_extents;
	// // // 	cairo_font_extents (cr, &font_extents);
	// // // 	double baseline = (FONT_SIZE - font_extents.height) * .5 + font_extents.ascent;
	// // // 	cairo_translate (cr, 0, baseline);
	// // // }
	// // // else
	// // // {
	// // // 	cairo_translate (cr, FONT_SIZE * .5, 0);
	// // // }

	// // // cairo_glyph_t *cairo_glyphs = cairo_glyph_allocate (len);
	// // // double current_x = 0;
	// // // double current_y = 0;
	// // // for (unsigned int i = 0; i < len; i++)
	// // // {
	// // // 	cairo_glyphs[i].index = info[i].codepoint;
	// // // 	cairo_glyphs[i].x = current_x + pos[i].x_offset / 64.;
	// // // 	cairo_glyphs[i].y = -(current_y + pos[i].y_offset / 64.);
	// // // 	current_x += pos[i].x_advance / 64.;
	// // // 	current_y += pos[i].y_advance / 64.;
	// // // }
	// // // cairo_show_glyphs (cr, cairo_glyphs, len);
	// // // cairo_glyph_free (cairo_glyphs);

	// // // cairo_surface_write_to_png (cairo_surface, "out.png");

	// // // cairo_font_face_destroy (cairo_face);
	// // // cairo_destroy (cr);
	// // // cairo_surface_destroy (cairo_surface);

	// hb_buffer_destroy (hb_buffer);
	// hb_font_destroy (hb_font);

	FT_Done_Face (ft_face);
	FT_Done_FreeType (library);

	std::cout << "It worked?" << std::endl;
}
