#include "../../../inc/slib/graphics/context.h"
#include "../../../inc/slib/graphics/image.h"

#include "../../../inc/slib/ui/core.h"
#include "../../../inc/slib/ui/platform.h"

#include "../../../inc/slib/core/file.h"
#include "../../../inc/slib/core/resource.h"

SLIB_UI_NAMESPACE_BEGIN
class _UI_GraphicsContext : public GraphicsContext
{
public:
	Size getFontTextSize(const Ref<Font>& font, const String& text)
	{
		return UI::getFontTextSize(font, text);
	}
	
	Rectangle getPathBounds(const Ref<GraphicsPath>& path)
	{
		return UI::getPathBounds(path);
	}
	
	sl_bool checkPointInPath(const Ref<GraphicsPath>& path, const Point& pt)
	{
		return UI::checkPointInPath(path, pt);
	}

	Ref<Drawable> createDrawableFromImage(const ImageDesc& desc)
	{
		return UI::createDrawableFromImage(desc);
	}
	
	Ref<Drawable> loadDrawableFromMemory(const void* mem, sl_size size)
	{
		return UI::loadDrawableFromMemory(mem, size);
	}
	
	Ref<Bitmap> createBitmap(sl_uint32 width, sl_uint32 height)
	{
		return UI::createBitmap(width, height);
	}
	
	Ref<Drawable> createDrawableFromBitmap(const Ref<Bitmap>& bitmap)
	{
		return UI::createDrawableFromBitmap(bitmap);
	}
	
	Ref<Bitmap> loadBitmapFromMemory(const void* mem, sl_size size)
	{
		return UI::loadBitmapFromMemory(mem, size);
	}
};

Ref<GraphicsContext> UI::getGraphicsContext()
{
	SLIB_SAFE_STATIC_REF(Ref<GraphicsContext>, ret);
	if (ret.isNull()) {
		ret = new _UI_GraphicsContext();
	}
	return ret;
}

Ref<Drawable> UI::createDrawableFromImage(const Ref<Image>& _image)
{
	Ref<Image> image = _image;
	if (image.isNotNull()) {
		ImageDesc desc;
		image->getDesc(desc);
		return createDrawableFromImage(desc);
	}
	return Ref<Drawable>::null();
}

Ref<Drawable> UI::loadDrawableFromMemory(const Memory& _mem)
{
	Memory mem = _mem;
	if (mem.isNotEmpty()) {
		return loadDrawableFromMemory(mem.getBuf(), mem.getSize());
	}
	return Ref<Drawable>::null();
}

Ref<Drawable> UI::loadDrawableFromFile(const String& filePath)
{
	Ref<Drawable> ret;
	Memory mem = File::readAllBytes(filePath);
	if (mem.isNotEmpty()) {
		ret = loadDrawableFromMemory(mem);
	}
	return ret;
}

Ref<Bitmap> UI::createBitmapFromImage(const ImageDesc& desc)
{
	Ref<Bitmap> ret = createBitmap(desc.width, desc.height);
	if (ret.isNotNull()) {
		ret->writePixels(0, 0, desc.width, desc.height, desc.colors, desc.stride);
		return ret;
	}
	return Ref<Bitmap>::null();
}

Ref<Bitmap> UI::createBitmapFromImage(const Ref<Image>& _image)
{
	Ref<Image> image = _image;
	if (image.isNotNull()) {
		ImageDesc desc;
		image->getDesc(desc);
		return createBitmapFromImage(desc);
	}
	return Ref<Bitmap>::null();
}

Ref<Drawable> UI::loadDrawableFromResource(const String& path)
{
	Ref<Drawable> ret;
	Memory mem = Resource::readAllBytes(path);
	if (mem.isNotEmpty()) {
		ret = loadDrawableFromMemory(mem);
	}
	return ret;
}

Ref<Bitmap> UI::loadBitmapFromMemory(const Memory& _mem)
{
	Memory mem = _mem;
	if (mem.isNotEmpty()) {
		return loadBitmapFromMemory(mem.getBuf(), mem.getSize());
	}
	return Ref<Bitmap>::null();
}

Ref<Bitmap> UI::loadBitmapFromFile(const String& filePath)
{
	Ref<Bitmap> ret;
	Memory mem = File::readAllBytes(filePath);
	if (mem.isNotEmpty()) {
		ret = loadBitmapFromMemory(mem);
	}
	return ret;
}

Ref<Bitmap> UI::loadBitmapFromResource(const String& path)
{
	Ref<Bitmap> ret;
	Memory mem = Resource::readAllBytes(path);
	if (mem.isNotEmpty()) {
		ret = loadBitmapFromMemory(mem);
	}
	return ret;
}
SLIB_UI_NAMESPACE_END
