#include "DrawableBase.h"
#include "BindableBase.h"

auto DrawableBase::Draw(Graphics &graphics) const noexcept(!IS_DEBUG) -> void
{
    for (auto &bind: bind_vector)
    {
        bind->Bind(graphics);
    }

    for (auto &b: GetStaticBinds())
    {
        b->Bind(graphics);
    }
    
    graphics.DrawIndexed(index_buffer_ptr->GetCount());
}

auto DrawableBase::AddBind(std::unique_ptr<Bindable> bind) noexcept(!IS_DEBUG) -> void
{
    assert("Must use AddIndexBuffer to bind index buffer" && typeid(*bind) != typeid(IndexBuffer));
    bind_vector.push_back(std::move(bind));
}

auto DrawableBase::AddIndexBuffer(std::unique_ptr<IndexBuffer> index_buffer_unique_ptr) noexcept -> void
{
    assert("Attempting to add index buffer a second time" && index_buffer_ptr == nullptr);
    index_buffer_ptr = index_buffer_unique_ptr.get();
    bind_vector.push_back(std::move(index_buffer_unique_ptr));
}
