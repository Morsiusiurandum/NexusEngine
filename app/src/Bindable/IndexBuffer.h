#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H
 
#include "Bindable.h"
#include <vector>

class IndexBuffer : public Bindable
{
public:
    IndexBuffer(Graphics &graphics, const std::vector<unsigned short> &index);

    auto Bind(Graphics &graphics) noexcept -> void override;

    [[nodiscard]] auto GetCount() const noexcept -> UINT;

private:
    UINT                                 count;
    Microsoft::WRL::ComPtr<ID3D11Buffer> index_buffer;
};

#endif //INDEX_BUFFER_H
