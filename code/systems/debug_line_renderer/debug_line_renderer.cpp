#include <systems/debug_line_renderer/debug_line_renderer.hpp>
#include <simple_renderer/lazy_include.hpp>
#include <vector>
#include <string>
#include <stdint.h>
#include <assert.h>


namespace
{
  struct Line
  {
    std::array<float, 3> from;
    std::array<float, 3> to;
    std::array<float, 3> color;
  };
  
  std::vector<Line> lines_to_render;
  
  renderer::shader line_shader;
  
  const renderer::vertex_buffer line_vertex_buffer({1.f, 0.f});
  const renderer::vertex_format line_vertex_format({
    renderer::attr_format_desc{"vs_in_line_end", renderer::attr_type::FLOAT},
  });
}


namespace Sys {
namespace Debug_line_renderer {


bool
initialize()
{
  const std::string tagged_shd_code = R"(
    [VERTEX]
    #version 150 core
  
    in float vs_in_line_end; // 1 for start, 0 for end
  
    uniform mat4 wvp;
    uniform vec3 start_position;
    uniform vec3 end_position;
    uniform vec3 color;
  
    out vec3 ps_in_color;
  
    void
    main()
    {
      ps_in_color = color;
      
      // Debug only so don't mind to much about the branch.
      if(vs_in_line_end > 0.0)
      {
        gl_Position = wvp * vec4(end_position, 1.0);
      }
      else
      {
        gl_Position = wvp * vec4(start_position, 1.0);
      }
    }
    [/VERTEX]
  
    [PIXEL]
    #version 150 core
    
    in vec3 ps_in_color;
  
    out vec4 ps_out_color;
  
    void
    main()
    {
      ps_out_color = vec4(ps_in_color, 1.0);
    }
    [/PIXEL]
  )";
  
  line_shader.load_shader(renderer::shader_utils::get_shader_code_from_tagged_string(tagged_shd_code));
  
  assert(line_shader.is_valid() && line_vertex_buffer.is_valid() && line_vertex_format.is_valid());
  if(!line_shader.is_valid() || !line_vertex_buffer.is_valid() || !line_vertex_format.is_valid())
  {
    return false;
  }

  const uint32_t size_hint = 512;
  lines_to_render.reserve(size_hint);

  return true;
}


void
add_line(std::array<float, 3> from, std::array<float,3> to, std::array<float,3> color)
{
  lines_to_render.emplace_back(Line{from, to, color});
}


void
render(std::array<float, 16> &wvp_mat)
{
//  for(auto &line : lines_to_render)
//  {
//    line_shader.set_raw_data("start_position",  &line.from[0],  sizeof(line.from));
//    line_shader.set_raw_data("end_position",    &line.to[0],    sizeof(line.to));
//    line_shader.set_raw_data("color",           &line.color[0], sizeof(line.color));
//    line_shader.set_raw_data("wvp",             &wvp_mat[0],    sizeof(wvp_mat));
//
//    line_shader.bind();
//    line_vertex_buffer.bind(line_vertex_format, line_shader);
//
//    glDrawArrays(GL_LINES, 0, 2);
//  }
  
  lines_to_render.clear();
}


} // ns
} // ns