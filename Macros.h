// Adapted from Will Shipley http://blog.wilshipley.com/2005/10/pimp-my-code-interlude-free-code.html
static inline BOOL IsEmpty(id thing) {
    return thing == nil || [thing isEqual:[NSNull null]]
        || ([thing respondsToSelector:@selector(length)]
        && [(NSData *)thing length] == 0)
        || ([thing respondsToSelector:@selector(count)]
        && [(NSArray *)thing count] == 0);
}

static inline NSString *StringFromObject(id object) {
	if (object == nil || [object isEqual:[NSNull null]]) {
		return @"";
	} else if ([object isKindOfClass:[NSString class]]) {
		return object;
	} else if ([object respondsToSelector:@selector(stringValue)]){
		return [object stringValue];
	} else {
		return [object description];
	}
}

static inline int signum(int n) { return (n < 0) ? -1 : (n > 0) ? +1 : 0; }

#pragma mark -
#pragma mark iOS Version

#define IOS_VERSION_EQUAL_TO(v)                  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedSame)
#define IOS_VERSION_GREATER_THAN(v)              ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedDescending)
#define IOS_VERSION_GREATER_THAN_OR_EQUAL_TO(v)  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedAscending)
#define IOS_VERSION_LESS_THAN(v)                 ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedAscending)
#define IOS_VERSION_LESS_THAN_OR_EQUAL_TO(v)     ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedDescending)

#pragma mark -
#pragma mark Syntactic sugar

#define NOT_ANIMATED NO
#define ANIMATED YES

#pragma mark -
#pragma mark UIColor

// example usage: UIColorFromHex(0x9daa76)
#define UIColorFromHex(hexValue) [UIColor colorWithRed:((float)((hexValue & 0xFF0000) >> 16))/255.0 green:((float)((hexValue & 0xFF00) >> 8))/255.0 blue:((float)(hexValue & 0xFF))/255.0 alpha:1.0]
#define UIColorFromHexWithAlpha(rgbValue,a) [UIColor colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0 green:((float)((rgbValue & 0xFF00) >> 8))/255.0 blue:((float)(rgbValue & 0xFF))/255.0 alpha:a]
#define UIColorFromRGBA(r,g,b,a) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:a]
#define UIColorFromRGB(r,g,b) UIColorFromRGBA(r,g,b,1.0)
#define UIColorRandomColor [UIColor colorWithHue:( arc4random() % 256 / 256.0 ) saturation:( arc4random() % 128 / 256.0 ) + 0.5 brightness:( arc4random() % 128 / 256.0 ) + 0.5 alpha:( arc4random() % 256 / 256.0 ) + 0.1]
#define UIColorRandomColorWithAlpha(a) [UIColor colorWithHue:( arc4random() % 256 / 256.0 ) saturation:( arc4random() % 128 / 256.0 ) + 0.5 brightness:( arc4random() % 128 / 256.0 ) + 0.5 alpha:a]

#define UIColorRed(color) CGColorGetComponents(color)[0]
#define UIColorGreen(color) CGColorGetComponents(color)[1]
#define UIColorBlue(color) CGColorGetComponents(color)[2]
#define UIColorAlpha(color) (CGColorGetNumberOfComponents(color) == 4 ? CGColorGetComponents(color)[3] : 1.0)

#pragma mark -
#pragma mark Collections

#define IDARRAY(...) (id []){ __VA_ARGS__ }
#define IDCOUNT(...) (sizeof(IDARRAY(__VA_ARGS__)) / sizeof(id))

#define ARRAY(...) [NSArray arrayWithObjects: IDARRAY(__VA_ARGS__) count: IDCOUNT(__VA_ARGS__)]

#define DICT(...) DictionaryWithIDArray(IDARRAY(__VA_ARGS__), IDCOUNT(__VA_ARGS__) / 2)

//The helper function unpacks the object array and then calls through to NSDictionary to create the dictionary:
static inline NSDictionary *DictionaryWithIDArray(id *array, NSUInteger count) {
    id keys[count];
    id objs[count];
    
    for(NSUInteger i = 0; i < count; i++) {
        keys[i] = array[i * 2];
        objs[i] = array[i * 2 + 1];
    }
    
    return [NSDictionary dictionaryWithObjects: objs forKeys: keys count: count];
}
#define POINTERIZE(x) ((__typeof__(x) []){ x })
#define NSVALUE(x) [NSValue valueWithBytes: POINTERIZE(x) objCType: @encode(__typeof__(x))]

#pragma mark -
#pragma mark Logging

#define LOG(fmt, ...) NSLog(@"[%s:%d] " fmt, __func__, __LINE__,  ## __VA_ARGS__)

#ifdef DEBUG
    #define INFO(fmt, ...) LOG(fmt, ## __VA_ARGS__)
#else
    // do nothing
    #define INFO(fmt, ...) 
#endif

#define ERROR(fmt, ...) LOG(fmt, ## __VA_ARGS__)

#pragma mark -
#pragma mark NSNumber

#define NUM_INT(int) [NSNumber numberWithInt:int]
#define NUM_FLOAT(float) [NSNumber numberWithFloat:float]
#define NUM_BOOL(bool) [NSNumber numberWithBool:bool]

#pragma mark -
#pragma mark Frame Geometry

#define CENTER_VERTICALLY(parent,child) floor((parent.frame.size.height - child.frame.size.height) / 2)
#define CENTER_HORIZONTALLY(parent,child) floor((parent.frame.size.width - child.frame.size.width) / 2)

// example: [[UIView alloc] initWithFrame:(CGRect){CENTER_IN_PARENT(parentView,500,500),CGSizeMake(500,500)}];
#define CENTER_IN_PARENT(parent,childWidth,childHeight) CGPointMake(floorf((parent.frame.size.width - childWidth) / 2),floorf((parent.frame.size.height - childHeight) / 2))
#define CENTER_IN_PARENT_X(parent,childWidth) floorf((parent.frame.size.width - childWidth) / 2)
#define CENTER_IN_PARENT_Y(parent,childHeight) floorf((parent.frame.size.height - childHeight) / 2)

#define CENTER_IN_PARENT_SIZE(parentSize, childWidth, childHeight) CGPointMake(floorf((parentSize.width - childWidth) / 2.0),floorf((parentSize.height - childHeight) / 2.0))

#define WIDTH(view) view.frame.size.width
#define HEIGHT(view) view.frame.size.height
#define X(view) view.frame.origin.x
#define Y(view) view.frame.origin.y
#define LEFT(view) view.frame.origin.x
#define TOP(view) view.frame.origin.y
#define BOTTOM(view) (view.frame.origin.y + view.frame.size.height) 
#define RIGHT(view) (view.frame.origin.x + view.frame.size.width) 

#define SET_FRAME_X(frame, x) (frame = CGRectMake(x, frame.origin.y, frame.size.width, frame.size.height))
#define SET_FRAME_Y(frame, y) (frame = CGRectMake(frame.origin.x, y, frame.size.width, frame.size.height))
#define SET_FRAME_WIDTH(frame, width) (frame = CGRectMake(frame.origin.x, frame.origin.y, width, frame.size.height))
#define SET_FRAME_HEIGHT(frame, height) (frame = CGRectMake(frame.origin.x, frame.origin.y, frame.size.width, height))
#define SET_FRAME_ORIGIN(frame, size) (frame = CGRectMake(origin.x, origin.y, frame.size.width, frame.size.height))
#define SET_FRAME_SIZE(frame, size) (frame = CGRectMake(frame.origin.x, frame.origin.y, size.width, size.height))

#define INT_FRAME_ORIGIN(frame) (frame = CGRectMake((int)frame.origin.x, (int)frame.origin.y, frame.size.width, frame.size.height))

#pragma mark -
#pragma mark IndexPath

#define INDEX_PATH(a,b) [NSIndexPath indexPathWithIndexes:(NSUInteger[]){a,b} length:2]

#pragma mark -
#pragma mark Device type. 
// Corresponds to "Targeted device family" in project settings
// Universal apps will return true for whichever device they're on. 
// iPhone apps will return true for iPhone even if run on iPad.

#define TARGETED_DEVICE_IS_IPAD (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
#define TARGETED_DEVICE_IS_IPHONE (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone)

#define IS_IPAD TARGETED_DEVICE_IS_IPAD
#define IS_IPHONE TARGETED_DEVICE_IS_IPHONE

#pragma mark -
#pragma mark Transforms

#define DEGREES_TO_RADIANS(degrees) degrees * M_PI / 180

#pragma mark -
#pragma mark UILabel

#define LABEL_SIZE(label) [label.text sizeWithFont:label.font constrainedToSize:CGSizeMake(WIDTH(label), CGFLOAT_MAX) lineBreakMode:label.lineBreakMode];