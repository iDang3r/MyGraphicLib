#import <Foundation/Foundation.h>

#import "MyObject.h"

@interface Form : NSWindow {
    MyCPPClass* _cppclass;
}
- (void)changeColor:(id)sender;
- (BOOL)windowShouldClose:(id)sender;
@end

@implementation Form
- (instancetype)init:(MyCPPClass*)cppclass {
    _cppclass = cppclass;

    [super initWithContentRect:NSMakeRect(300, 300, 200, 80) styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable backing:NSBackingStoreBuffered defer:NO];
    [self setTitle:@"ColorDialog"];
    [self setIsVisible:YES];
    [self makeKeyAndOrderFront:self];

    NSLog(@"Button in!");
    NSColorPanel* colorDialog = [NSColorPanel sharedColorPanel];
    [colorDialog setIsVisible:YES];
    [colorDialog setColor:[NSColor cyanColor]];
    NSLog(@"Button out!");

    return self;
}

- (void)changeColor:(id)sender {
    NSLog(@"changeColor!");
    [self setBackgroundColor:[(NSColorPanel*)sender color]];
    NSColor* color = [(NSColorPanel*)sender color];
    _cppclass->test_call();

    NSLog(@"r = %f, g = %f, b = %f", [color redComponent], [color greenComponent], [color blueComponent]);
    _cppclass->setColor_cpp(Color([color redComponent], [color greenComponent], [color blueComponent]));

    NSLog(@"color = %@", [(NSColorPanel*)sender color]);
}

- (BOOL)windowShouldClose:(id)sender {
    NSLog(@"ShoulClose!");
    [NSApp terminate:sender];
    return NO;
}
@end

@implementation MyObject

MyClassImpl::MyClassImpl(MyCPPClass* cppclass)
    : self( [[MyObject alloc] init] ), _cppclass(cppclass)
{
    _cppclass->setColor_cpp(Color(0.17, 0.0, 1.0));
}

MyClassImpl::~MyClassImpl()
{
    [(id)self dealloc];
}

void MyClassImpl::runPalette()
{
    [NSApplication sharedApplication];
    [[[[Form alloc] init:_cppclass] autorelease] makeMainWindow];
    [NSApp run];
}

int MyClassImpl::doSomethingWith(int aParameter)
{
    int result = aParameter;

    result *= result;
    // ... some code to calculate the result

    NSLog(@"Done!");

    return result;
}

@end