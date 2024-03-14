#include "Drawable.h"
#include "../Bindable/BindableBase.h"

auto Drawable::Draw(Graphics &graphics) const noexcept(!IS_DEBUG) -> void
{
    for (auto &bind: bind_vector)
    {
        bind->Bind(graphics);
    }

    graphics.DrawIndexed(index_buffer->GetCount());
}

auto Drawable::AddBind(std::unique_ptr<Bindable> bind) noexcept(!IS_DEBUG) -> void
{
    assert("Must use AddIndexBuffer to bind index buffer" && typeid(*bind) != typeid(IndexBuffer));
    bind_vector.push_back(std::move(bind));
}

auto Drawable::AddIndexBuffer(std::unique_ptr<IndexBuffer> index_buffer_unique_ptr) noexcept -> void
{
    assert("Attempting to add index buffer a second time" && index_buffer == nullptr);
    index_buffer = index_buffer_unique_ptr.get();
    bind_vector.push_back(std::move(index_buffer_unique_ptr));
}
