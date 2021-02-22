#include <library/opengl/oglfont.hpp>

#include <library/bitmap/bitmap.hpp>
#include <library/math/matrix.hpp>
#include <library/opengl/opengl.hpp>
#include <library/opengl/texture.hpp>
#include <stdexcept>

namespace library
{
<<<<<<< HEAD
	SimpleFont::SimpleFont()
		: tilesize(0), lastUnit(-1), max_vertices(0), vdata(nullptr)
	{
		setClip(glm::vec2(0.0));
	}
	SimpleFont::~SimpleFont()
	{
		delete[] vdata;
	}

	void SimpleFont::bind(GLenum unit)
	{
		// bind font shader
		shader->bind();
		if (this->lastUnit != unit)
		{
			this->lastUnit = unit;
			// resend texture slot to shader
			shader->sendInteger("fontimage", unit);
		}
		// bind texture
		texture->bind(unit);
	}

	void SimpleFont::setClip(const glm::vec2& clip)
	{
		this->clip = clip;
		// Y-axis goes positively upwards
		font_windings_up =
		{
			clip.x, clip.y,   1-clip.x, clip.y,   1-clip.x, 1-clip.y,   clip.x, 1-clip.y
		};
		// Y-axis goes positively downwards
		font_windings_down =
		{
			clip.x, 1-clip.y,   1-clip.x, 1-clip.y,   1-clip.x, clip.y,   clip.x, clip.y
		};
	}

	void SimpleFont::print(const glm::vec3& location, const glm::vec2& size, std::string text, bool YaxisUp)
	{
		// vertex count
		int current_vertices = text.length();
		if (current_vertices == 0) return;
		current_vertices *= 4;

		/// create vertex array ///
		resizeVertexArray(current_vertices);

		font_vertex_t* vertex = this->vdata;
		std::vector<float>& windings = (YaxisUp) ? font_windings_up : font_windings_down;

		/// emit vertex data
		emitTextBlock(vertex, location, size, text, windings);

		// upload to GPU and render
		upload(current_vertices);
		render();
	}
	void SimpleFont::serialUpload(std::vector<SimpleFont::print_data_t>& data, bool YaxisUp)
	{
		// vertex count
		int current_vertices = 0;
		for (size_t i = 0; i < data.size(); i++)
			current_vertices += data[i].text.length();

		if (current_vertices == 0) return;
		current_vertices *= 4;

		/// create vertex array ///
		resizeVertexArray(current_vertices);

		font_vertex_t* vertex = this->vdata;
		std::vector<float>& windings = (YaxisUp) ? font_windings_up : font_windings_down;

		/// emit vertex data for each data structure
		for (size_t i = 0; i < data.size(); i++)
		{
			emitTextBlock(vertex, data[i].location, data[i].size, data[i].text, windings);
		}

		// upload to GPU and render
		upload(current_vertices);
	}

	void SimpleFont::resizeVertexArray(int verts)
	{
		// vertex data
		if (this->max_vertices < verts)
		{
			// delete any old data
			delete[] this->vdata;
			// resize when too small
			this->max_vertices = verts;
			this->vdata = new font_vertex_t[this->max_vertices];
		}
	}

	void SimpleFont::emitTextBlock(font_vertex_t*& vertex, const glm::vec3& location, const glm::vec2& size, std::string& text, const std::vector<float>& wind)
	{
		for (size_t i = 0; i < text.length(); i++)
		{
			// convert text to font array index positions
			text[i] -= 32;

			#define clipInt(x) ((x > 0.5) ? 1 : 0)

			// emit characters as quads
			vertex->x = location.x + (clipInt(wind[0]) + i) * size.x;
			vertex->y = location.y + 0.0;
			vertex->z = location.z;
			vertex->s = wind[0];
			vertex->t = wind[1];
			vertex->p = text[i];
			vertex++;

			vertex->x = location.x + (clipInt(wind[2]) + i) * size.x;
			vertex->y = location.y + 0.0;
			vertex->z = location.z;
			vertex->s = wind[2];
			vertex->t = wind[3];
			vertex->p = text[i];
			vertex++;

			vertex->x = location.x + (clipInt(wind[4]) + i) * size.x;
			vertex->y = location.y + size.y;
			vertex->z = location.z;
			vertex->s = wind[4];
			vertex->t = wind[5];
			vertex->p = text[i];
			vertex++;

			vertex->x = location.x + (clipInt(wind[6]) + i) * size.x;
			vertex->y = location.y + size.y;
			vertex->z = location.z;
			vertex->s = wind[6];
			vertex->t = wind[7];
			vertex->p = text[i];
			vertex++;
		}
	}

	void SimpleFont::upload(int verts)
	{
		// upload data to vao
		if (vao.good() == false)
		{
			vao.begin(sizeof(font_vertex_t), verts, this->vdata, GL_STREAM_DRAW);
			vao.attrib(0, 3, GL_FLOAT, GL_FALSE, offsetof(font_vertex_t, x));
			vao.attrib(1, 3, GL_FLOAT, GL_FALSE, offsetof(font_vertex_t, s));
			vao.end();
		}
		else
		{
			vao.upload(sizeof(font_vertex_t), verts, this->vdata, GL_STREAM_DRAW);
		}
	}

	// a simple render call
	void SimpleFont::render()
	{
		vao.render(GL_QUADS);
	}

	Texture* SimpleFont::createTexture(const std::string& filename, int tilesize)
	{
		if (tilesize <= 1)
			throw std::string("SimpleFont::createTexture: Invalid tile size");

		// FIXME: assuming PNG format
		Bitmap fontImage(filename, Bitmap::PNG);
		if (fontImage.isValid() == false)
			throw std::string("SimpleFont::createTexture: Bitmap ended up invalid");

		fontImage.parse2D(tilesize, tilesize);

		// create texture, upload image data
		texture = new Texture(GL_TEXTURE_2D_ARRAY);
		texture->create(fontImage, true, GL_CLAMP_TO_EDGE, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);

		return texture;
	}
=======
SimpleFont::SimpleFont() : tilesize(0), lastUnit(-1) { setClip(glm::vec2(0.0)); }
>>>>>>> parent of b877676... bring in mindchilds oglfont fixes

void SimpleFont::bind(GLenum unit)
{
    // bind font shader
    shader->bind();
    if (this->lastUnit != unit)
    {
        this->lastUnit = unit;
        // resend texture slot to shader
        shader->sendInteger("fontimage", unit);
    }
    // bind texture
    texture->bind(unit);
}

void SimpleFont::setClip(const glm::vec2& clip)
{
    this->clip = clip;
    // Y-axis goes positively upwards
    font_windings_up = {clip.x,     1 - clip.y, 1 - clip.x, 1 - clip.y,
                        1 - clip.x, clip.y,     clip.x,     clip.y};
    // Y-axis goes positively downwards
    font_windings_down = {clip.x,     clip.y,     1 - clip.x, clip.y,
                          1 - clip.x, 1 - clip.y, clip.x,     1 - clip.y};
}

void SimpleFont::print(const glm::vec3& location, const glm::vec2& size, std::string text,
                       bool YaxisUp)
{
    vdata.clear();
    idata.clear();
    std::vector<float>& windings = (YaxisUp) ? font_windings_up : font_windings_down;

    /// emit vertex data
    emitTextBlock(location, size, text, windings);

    // upload to GPU and render
    this->upload();
    this->render();
}
void SimpleFont::serialPrint(std::vector<SimpleFont::print_data_t>& data, bool YaxisUp)
{
    vdata.clear();
    idata.clear();
    std::vector<float>& windings = (YaxisUp) ? font_windings_up : font_windings_down;

    /// emit vertex data for each data structure
    for (size_t i = 0; i < data.size(); i++)
    { emitTextBlock(data[i].location, data[i].size, data[i].text, windings); }

    // upload to GPU and render
    this->upload();
    this->render();
}

void SimpleFont::emitTextBlock(const glm::vec3& location, const glm::vec2& size, std::string& text,
                               const std::vector<float>& wind)
{
    for (size_t i = 0; i < text.length(); i++)
    {
        // convert text to font array index positions
        const char c = text[i] - 32;
        const int tex_s = c % 16;
        const int tex_t = c / 16;

#define clipInt(x) ((x > 0.5) ? 1 : 0)

        const size_t idx = vdata.size();
        // emit characters as quads
        vdata.push_back(font_vertex_t{.x = location.x + (clipInt(wind[0]) + i) * size.x,
                                      .y = location.y + 0.0f,
                                      .z = location.z,
                                      .s = (tex_s + wind[0]) / 16.0f,
                                      .t = (tex_t + wind[1]) / 16.0f});

        vdata.push_back(font_vertex_t{.x = location.x + (clipInt(wind[2]) + i) * size.x,
                                      .y = location.y + 0.0f,
                                      .z = location.z,
                                      .s = (tex_s + wind[2]) / 16.0f,
                                      .t = (tex_t + wind[3]) / 16.0f});

        vdata.push_back(font_vertex_t{.x = location.x + (clipInt(wind[4]) + i) * size.x,
                                      .y = location.y + size.y,
                                      .z = location.z,
                                      .s = (tex_s + wind[4]) / 16.0f,
                                      .t = (tex_t + wind[5]) / 16.0f});

        vdata.push_back(font_vertex_t{.x = location.x + (clipInt(wind[6]) + i) * size.x,
                                      .y = location.y + size.y,
                                      .z = location.z,
                                      .s = (tex_s + wind[6]) / 16.0f,
                                      .t = (tex_t + wind[7]) / 16.0f});

        idata.push_back(idx + 0);
        idata.push_back(idx + 1);
        idata.push_back(idx + 2);
        idata.push_back(idx + 2);
        idata.push_back(idx + 3);
        idata.push_back(idx + 0);
    }
}

void SimpleFont::upload()
{
    // upload data to vao
    if (vao.good() == false)
    {
        vao.begin(sizeof(font_vertex_t), vdata.size(), vdata.data(), GL_STREAM_DRAW);
        vao.attrib(0, 3, GL_FLOAT, GL_FALSE, offsetof(font_vertex_t, x));
        vao.attrib(1, 2, GL_FLOAT, GL_FALSE, offsetof(font_vertex_t, s));
    }
    else
    {
        vao.upload(sizeof(font_vertex_t), vdata.size(), vdata.data(), GL_STREAM_DRAW);
    }
    vao.indexes(idata.data(), idata.size());
}

// a simple render call
void SimpleFont::render() { vao.renderIndexed(GL_TRIANGLES); }

Texture* SimpleFont::createTexture(const std::string& filename, int tilesize)
{
    if (tilesize <= 1) throw std::runtime_error("SimpleFont::createTexture: Invalid tile size");

    // FIXME: assuming PNG format
    const Bitmap fontImage(filename, Bitmap::PNG);
    if (fontImage.isValid() == false)
        throw std::runtime_error("SimpleFont::createTexture: Bitmap ended up invalid");

    // create texture, upload image data
    texture = new Texture(GL_TEXTURE_2D);
    texture->create(fontImage, true, GL_CLAMP_TO_EDGE, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);

    return texture;
}

} // namespace library
