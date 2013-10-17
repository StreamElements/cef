// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_LIBCEF_BROWSER_TEXT_INPUT_CLIENT_OSR_MAC_H_
#define CEF_LIBCEF_BROWSER_TEXT_INPUT_CLIENT_OSR_MAC_H_
#pragma once

#import <Cocoa/Cocoa.h>
#include <vector>

#include "libcef/browser/render_widget_host_view_osr.h"

#include "base/mac/scoped_nsobject.h"
#include "base/strings/string16.h"
#include "content/browser/renderer_host/render_widget_host_impl.h"
#include "content/common/edit_command.h"
#include "third_party/WebKit/public/web/WebCompositionUnderline.h"

// Implementation for the NSTextInputClient protocol used for enabling IME on
// mac when window rendering is disabled.

@interface CefTextInputClientOSRMac : NSObject<NSTextInputClient> {

 @public
  // The range of current marked text inside the whole content of the DOM node
  // being edited.
  NSRange markedRange_;

  // The current composition character range and its bounds.
  gfx::Range composition_range_;
  std::vector<gfx::Rect> composition_bounds_;

  // The current caret bounds.
  gfx::Rect caret_rect_;

 @private
  // Represents the input-method attributes supported by this object.
  base::scoped_nsobject<NSArray> validAttributesForMarkedText_;

  // Indicates if we are currently handling a key down event.
  BOOL handlingKeyDown_;

  // Indicates if there is any marked text.
  BOOL hasMarkedText_;

  // Indicates whether there was any marked text prior to handling
  // the current key event.
  BOOL oldHasMarkedText_;

  // Indicates if unmarkText is called or not when handling a keyboard
  // event.
  BOOL unmarkTextCalled_;

  // The selected range, cached from a message sent by the renderer.
  NSRange selectedRange_;

  // Text to be inserted which was generated by handling a key down event.
  string16 textToBeInserted_;

  // Marked text which was generated by handling a key down event.
  string16 markedText_;

  // Underline information of the |markedText_|.
  std::vector<WebKit::WebCompositionUnderline> underlines_;

  // Indicates if doCommandBySelector method receives any edit command when
  // handling a key down event.
  BOOL hasEditCommands_;

  // Contains edit commands received by the -doCommandBySelector: method when
  // handling a key down event, not including inserting commands, eg. insertTab,
  // etc.
  content::EditCommands editCommands_;

  CefRenderWidgetHostViewOSR* renderWidgetHostView_;
}

@property(nonatomic, readonly) NSRange selectedRange;
@property(nonatomic) BOOL handlingKeyDown;

- (id)initWithRenderWidgetHostViewOSR:(CefRenderWidgetHostViewOSR*) rwhv;
- (void)HandleKeyEventBeforeTextInputClient:(NSEvent*)keyEvent;
- (void)HandleKeyEventAfterTextInputClient:(NSEvent*)keyEvent;
- (void)cancelComposition;

@end

#endif  // CEF_LIBCEF_BROWSER_TEXT_INPUT_CLIENT_OSR_MAC_H_