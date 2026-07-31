#ifndef NW_LYT_TEXTBOX_H_
#define NW_LYT_TEXTBOX_H_

#include <nw/lyt/lyt_Pane.h>

// Silent VSCode
typedef wchar_t char16;

namespace nw { namespace font {

class DispStringBuffer;
class Font;

template <typename CharType>
class TagProcessorBase;

} } // namespace nw::font

namespace nw { namespace lyt {

// TODO
class TextBox : public Pane
{
public:
    typedef font::TagProcessorBase<char16> TagProcessor;

public:
    NW_UT_RUNTIME_TYPEINFO(TextBox::Base);

    TextBox();
    virtual ~TextBox();

    const ut::Color8 GetVtxColor(u32 idx) const override; // deleted
    void SetVtxColor(u32 idx, ut::Color8 value) override;

    u8 GetVtxColorElement(u32 idx) const override; // deleted
    void SetVtxColorElement(u32 idx, u8 value) override;

    Material* GetMaterial(u32 idx) const override;
    u8 GetMaterialNum() const override;

    void CalculateMtx(Pane::CalculateMtxContext& drawInfo, bool isDirtyParentMtx) override;

protected:
    void DrawSelf(DrawInfo& drawInfo) override;
    void LoadMtx(DrawInfo& drawInfo) override;

public:
    virtual void AllocStringBuffer(u16 minLen);
    virtual void FreeStringBuffer();

    virtual u16 SetString(const char16* str, u16 dstIdx = 0);
    virtual u16 SetString(const char16* str, u16 dstIdx, u16 strLen);

private:
    char16* m_TextBuf;
    const char* m_TextID;
    ut::Color8 m_TextColors[TEXTCOLOR_MAX];
    const font::Font* m_pFont;
    Size m_FontSize;
    f32 m_LineSpace;
    f32 m_CharSpace;
    TagProcessor* m_pTagProcessor;
    u16 m_TextBufLen;
    u16 m_TextLen;
    u8 m_TextPosition;
    f32 m_ItalicRatio;
    math::VEC2 m_ShadowOffset;
    math::VEC2 m_ShadowScale;
    ut::Color4u8 m_ShadowTopColor;
    ut::Color4u8 m_ShadowBottomColor;
    f32 m_ShadowItalicRatio;

    struct Bits
    {
        u8 textAlignment: 2;
        u8 isPTDirty: 1;
        bool shadowEnabled: 1;
        bool invisibleBorderEnabled: 1;
        bool doubleDrawnBorderEnabled: 1;
        bool widthLimitEnabled: 1;
    };

    Bits m_Bits;

    Material* m_pMaterial;
    font::DispStringBuffer* m_pDispStringBuf;
    void* m_pFontGraphicsBuf;
};
static_assert(sizeof(TextBox) == 0x104);

} } // namespace nw::lyt

#endif // NW_LYT_TEXTBOX_H_
