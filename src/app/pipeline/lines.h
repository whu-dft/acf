/*! -*-c++-*-
  @file   lines.h
  @author David Hirvonen
  @brief Declaration of ogles_gpgpu shader for drawing lines.

  \copyright Copyright 2017-2018 Elucideye, Inc. All rights reserved.
  \license{This project is released under the 3 Clause BSD License.}

*/

#ifndef __acf_LineShader_h__
#define __acf_LineShader_h__

#include <ogles_gpgpu/common/common_includes.h>
#include <ogles_gpgpu/common/types.h>
#include <ogles_gpgpu/common/proc/base/filterprocbase.h>
#include <ogles_gpgpu/platform/opengl/gl_includes.h>

#include <array>
#include <memory>

namespace ogles_gpgpu {
class Shader;
}  // namespace ogles_gpgpu

BEGIN_OGLES_GPGPU

// Ideally we would use GL_TRIANGLES + glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
// However, this isn't supported in OpenGL ES
// https://stackoverflow.com/a/29583687
// https://stackoverflow.com/a/4063084

class LineShader
{
public:
    using Point2d = std::array<float, 2>;

    LineShader();

    static const char* getProcName();
    void draw(int outFrameW, int outFrameH);
    void setModlViewTransformation(const Mat44f& mvp);
    void setLineSegments(const std::vector<Point2d>& segments);

protected:
    std::shared_ptr<Shader> shader;

    static const char* vshaderColorSrc;
    static const char* fshaderColorSrc;

    GLint shParamUColor;
    GLint shParamUMVP;
    GLint shParamAPosition;

    std::vector<Point2d> points;
    std::array<float, 3> color = { { 0.f, 1.f, 0.f } };
    Mat44f MVP{};
};

class LineProc : public ogles_gpgpu::FilterProcBase
{
public:
    using Point2d = std::array<float, 2>;

    LineProc() = default;

    const char* getProcName() override
    {
        return "LineProc";
    }
    const char* getFragmentShaderSource() override
    {
        return fshaderLineSrc;
    }
    void filterRenderDraw() override;

    void setLineSegments(const std::vector<Point2d>& segments);

    void setModlViewTransformation(const Mat44f& mvp);

    static const char* fshaderLineSrc; // fragment shader source

    LineShader lines;
};

END_OGLES_GPGPU

#endif // __drishti_graphics_LineShader_h__
