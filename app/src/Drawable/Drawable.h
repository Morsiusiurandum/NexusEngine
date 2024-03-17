#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "BindableBase.h"
#include "DrawableBase.h"

template<class T>
class Drawable : public DrawableBase
{
protected:
    static auto IsStaticInitialized() noexcept -> bool
    {
        return !staticBinds.empty();
    }

    static void AddStaticBind(std::unique_ptr<Bindable> bind) noexcept(!IS_DEBUG)
    {
        assert("*Must* use AddStaticIndexBuffer to bind index buffer" && typeid(*bind) != typeid(IndexBuffer));
        staticBinds.push_back(std::move(bind));
    }
    void AddStaticIndexBuffer(std::unique_ptr<IndexBuffer> index_buffer) noexcept(!IS_DEBUG)
    {
        assert("Attempting to add index buffer a second time" && index_buffer_ptr == nullptr);
        index_buffer_ptr = index_buffer.get();
        staticBinds.push_back(std::move(index_buffer));
    }
    void SetIndexFromStatic() noexcept(!IS_DEBUG)
    {
        assert("Attempting to add index buffer a second time" && index_buffer_ptr == nullptr);
        for (const auto &b: staticBinds)
        {
            if (const auto p = dynamic_cast<IndexBuffer *>(b.get()))
            {
                index_buffer_ptr = p;
                return;
            }
        }
        assert("Failed to find index buffer in static binds" && index_buffer_ptr != nullptr);
    }

private:
    [[nodiscard]] auto GetStaticBinds() const noexcept -> const std::vector<std::unique_ptr<Bindable>> & override
    {
        return staticBinds;
    }

private:
    static std::vector<std::unique_ptr<Bindable>> staticBinds;
};

template<class T>
std::vector<std::unique_ptr<Bindable>> Drawable<T>::staticBinds;

#endif //DRAWABLE_H
