#ifndef NW_LYT_PANE_H_
#define NW_LYT_PANE_H_

#include <nw/ut/ut_Color.h>
#include <nw/ut/ut_LinkList.h>
#include <nw/ut/ut_RuntimeTypeInfo.h>

#include <nw/lyt/lyt_Types.h>

namespace nw { namespace lyt { namespace internal {

class PaneBase
{
    NW_DISALLOW_COPY_AND_ASSIGN(PaneBase);

public:
    PaneBase();
    virtual ~PaneBase();

public:
    ut::LinkListNode m_Link;
};
static_assert(sizeof(PaneBase) == 0xC);

} } } // namespace nw::lyt::internal

namespace nw { namespace lyt { namespace res {

struct ExtUserDataList;

} } } // namespace nw::lyt::res

namespace nw { namespace lyt {

class AnimTransform;
class Material;
class DrawInfo;
class Pane;

typedef ut::LinkList<Pane, offsetof(internal::PaneBase, m_Link)> PaneList;

// TODO
class Pane : public internal::PaneBase
{
public:
    NW_UT_RUNTIME_TYPEINFO_ROOT();

public:
    Pane();
    virtual ~Pane();

    virtual const ut::Color8 GetVtxColor(u32 idx) const; // deleted
    virtual void SetVtxColor(u32 idx, ut::Color8 value); // deleted

    virtual u8 GetColorElement(u32 idx) const; // deleted
    virtual void SetColorElement(u32 idx, u8 value);

    virtual u8 GetVtxColorElement(u32 idx) const; // deleted
    virtual void SetVtxColorElement(u32 idx, u8 value);

    virtual Material* GetMaterial(u32 idx) const;
    virtual u8 GetMaterialNum() const;

    virtual Pane* FindPaneByName(const char* findName, bool bRecursive = true);
    virtual Material* FindMaterialByName(const char* findName, bool bRecursive = true);

    virtual void BindAnimation(AnimTransform* pAnimTrans, bool bRecursive = true, bool bEnable = true); // deleted
    virtual void UnbindAnimation(AnimTransform* pAnimTrans, bool bRecursive = true); // deleted
    virtual void UnbindAnimationSelf(AnimTransform* pAnimTrans); // deleted

    struct CalculateMtxContext
    {
        // TODO
    };

    virtual void CalculateMtx(CalculateMtxContext& context, bool isDirtyParentMtx);
    virtual void Draw(DrawInfo& drawInfo);
    virtual void DrawSelf(DrawInfo& drawInfo);

protected:
    virtual void LoadMtx(DrawInfo& drawInfo);
    virtual Pane* FindPaneByNameRecursive(const char* findName);
    virtual Material* FindMaterialByNameRecursive(const char* findName);

private:
    Pane* m_pParent;
    PaneList m_ChildList;
    math::VEC3 m_Translate;
    math::VEC3 m_Rotate;
    math::VEC2 m_Scale;
    Size m_Size;

    // NW_STATIC_ASSERT((
    //     sizeof(math::VEC3) + // m_Translate
    //     sizeof(math::VEC3) + // m_Rotate
    //     sizeof(math::VEC2) + // m_Scale
    //     sizeof(Size)) / // m_Size
    //     sizeof(f32) == ANIMTARGET_PANE_MAX
    // );

    u8 m_Flag;
    u8 m_Alpha;
    u8 m_GlbAlpha;
    u8 m_BasePosition;
    math::MTX34 m_GlbMtx;
    const math::MTX34* m_UserMtx;
    const res::ExtUserDataList* m_pExtUserDataList;
    char m_Name[ResourceNameStrMax + 1];
    char m_UserData[UserDataStrMax + 1];
};
static_assert(sizeof(Pane) == 0xA4);

} } // namespace nw::lyt

#endif // NW_LYT_PANE_H_
