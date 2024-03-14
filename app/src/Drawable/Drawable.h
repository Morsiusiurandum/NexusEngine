#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <DirectXMath.h>
#include "../Graphics.h"

class Bindable;

class Drawable
{
public:
    Drawable()                 = default;
    Drawable(const Drawable &) = delete;

    virtual ~Drawable()                                               = default;
    virtual auto Update(float dt) noexcept -> void                    = 0;
    virtual auto GetTransformXM() const noexcept -> DirectX::XMMATRIX = 0;

    auto Draw(Graphics &graphics) const noexcept(!IS_DEBUG) -> void;
    auto AddBind(std::unique_ptr<Bindable> bind) noexcept(!IS_DEBUG) -> void;
    auto AddIndexBuffer(std::unique_ptr<class IndexBuffer> index_buffer_uptr) noexcept -> void;

private:
    const IndexBuffer                     *index_buffer = nullptr;
    std::vector<std::unique_ptr<Bindable>> bind_vector;
};

#endif //DRAWABLE_H
