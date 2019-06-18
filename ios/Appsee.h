//
//  Appsee.h
//  Appsee v2.6.1
//
//  Copyright (c) 2019 Shift 6 Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <CoreMedia/CoreMedia.h>
#import <CoreVideo/CoreVideo.h>
#import <QuartzCore/QuartzCore.h>
#import <SystemConfiguration/SystemConfiguration.h>
#import <Security/Security.h>

@protocol AppseeDelegate;

/********************************************************************************************
    Appsee SDK.
    To use, simply call 'start:' in your 'applicationDidFinishLaunching:withOptions:' method. 
 *******************************************************************************************/

@interface AppseeWFRN: NSObject

/***************
 General Control
 **************/

/** Starts recording screen and user gestures. This method should only be called once.
 * Recording will stop (and video will be uploaded) when app is in the background.
 * A new session will start when the app is returned from background.
 * Apps using this method should place their API key in the main bundle's Info.plist file, under the "com.appsee.ApiKey" entry.
*/
+(void)start;

/** Starts recording screen and user gestures. This method should only be called once.
 * Recording will stop (and video will be uploaded) when app is in the background.
 * A new session will start when the app is returned from background.
 * @param apiKey The application-specific API key from (available in your Appsee dashboard).
 */
+(void)start:(NSString*) apiKey;

/** Stops the current video (session tracking will continue). Usually, this method shouldn't be called unless you explictly want to stop video recording.  
 */
+(void)stop;

/**
 * Finishes the current session and uploads it (in the background). Usually, this method shouldn't be called unless you
 * explicitly want to stop recording and force uploading at some point in your app, before the user minimizes it.
 @param verifyBackground Finish the session only if app is in background (pass 'NO' unless you have a Voip app).
 @param shouldUpload Upload the session immediately, or wait until the app is in the background.
 */
+(void)finishSession:(BOOL)verifyBackground upload:(BOOL)shouldUpload;

/**
 * Upload previous sessions. This method should not be called unless your app is never in the background and you want to upload 
 * sessions on the foreground.
 */
+(void)upload;

/**
 * Force Appsee to start a new session (if not already running). Applicable only when a prior session was manually finished using finishSession:upload:
 */
+(void)forceNewSession;

/**
 * Pause recording of the video. To resume, call 'resume'.
 */
+(void)pause;

/** Resume recording of the video.
 */
+(void)resume;

/** Enable Appsee event-logging to NSLog.
 @param log YES to turn on debug logging, NO to turn them off.
 */
+(void)setDebugToNSLog:(BOOL)log;

/** Set whether to opt-out of using Appsee in the current device (default is false).
* @param isOptOut YES to opt-out current device, NO to opt-in.
*/
+(void)setOptOutStatus:(BOOL)isOptOut;

/** Get the opt-out status of the current device.
* By default, devices are opted-in, meaning this method would return false.
* @return a boolean value stating whether current device is opted-out.
*/
+(BOOL)getOptOutStatus;

/** Set the recording consent given by the user. This should be used in cases where you are asking for the user
 * consent not through Appsee.
 * @param approved YES if the user has approved recording.
 */
+(void)setRecordingConsent:(BOOL)approved;

/** Get the recording consent status, as given by the user.
 * @return an NSNumber value stating whether the user has given a consent for recording.
 * If the consent was never asked, a nil value will be returned. Otherwise - @YES/@NO.
 */
+(NSNumber*)getRecordingConsent;

/** Delete all local and remote data for the current user. This method also unsets the current active user, and opts out this device from future tracking.
 Note: this method performs a synchronous call to the Appsee servers and is therefore recommended to be performed on a side thread.
 @return a boolean value stating whether deletion was successful. Failure may occur in case the Appsee servers cannot be reached (in case there is no connectivity) - and the method should be retried.
 */
+(BOOL)deleteCurrentUserData;

/****************************
 Application Events & Screens
 ***************************/

/** Add a timed application event (such as: user reached a specific level or screen).
 @param eventName The name of the event (ie: "WelcomeScreen").
 */
+(void)addEvent:(NSString*)eventName;

/** Add a timed application event (such as: user reached a specific level or screen) along with custom properties.
 @param eventName The name of the event (ie: "Level").
 @param properties Key-value pairs with custom properties for the event. Properties must be NSNumbers, NSStrings, NSDates, NSURL, or NSNull. Keys must be NSStrings.
 */
+(void)addEvent:(NSString*)eventName withProperties:(NSDictionary *)properties;

/** Mark the appearance starting time of a screen.
 This method should be usually called from the viewDidAppear: method.
 @param screenName The name of the screen (ie: "WelcomeScreen").
 */
+(void)startScreen:(NSString*)screenName;

/** Add a custom action to the current screen.
 @param actionName The name of the action (ie: "MyButtonClick").
 */
+(void)addScreenAction:(NSString*)actionName;

/** Overlay an image on top of the next video frame.
 @param image The image to overlay. Can be 'nil' to stop overlaying any image.
 @param rect The image's location in the screen.
 */
+(void)overlayImage:(UIImage*)image inRect:(CGRect)rect;

/************************
 Setting User Information
 ************************/
 
/** Set the app's user ID. Pass nil to log out the current user.
 @param userID The application-specific user identifier.
 */
+(void)setUserID:(NSString*)userID;

/** Set a property for the current user.
 Please call [setUserID:(NSString*)userID] to set the current user.
 @param propertyName The name of the property to set. Must be an NSString.
 @param propertyValue The value of the property to set. Must be NSNumbers, NSStrings, NSDates, NSURL, or NSArray of NSStrings.

 */
+(void)setUserProperty:(NSString*)propertyName withValue:(id)propertyValue;

/** Set multiple (key-value) properties for the current user.
 Please call [setUserID:(NSString*)userID] to set the current user.
 Dictionary keys must be NSStrings.
 @param userProperties The user properties to set. Keys must be NSStrings. Properties must be NSNumbers, NSStrings, NSDates, NSURL, or NSArray of NSStrings.
 */
+(void)setUserProperties:(NSDictionary*)userProperties;

/** Increment the value of a numeric property.
 @param propertyName The name of the user property.
 @param value The value to increment or decrement by (if negative).
 */
+(void)incUserProperty:(NSString *)propertyName incrementBy:(NSNumber *)value;

/** Append an item to a list property.
 @param propertyName The name of the user property.
 @param item The item to append.
 */
+(void)appendToUserProperty:(NSString *)propertyName listItem:(NSString *)item;

/** Unsets a property for the current user.
 @param propertyName The name of the user property.
 */
+(void)removeUserProperty:(NSString*)propertyName;

/** Set the user's location.
 @param latitude Latitude.
 @param longitude Longitude.
 @param horizontalAccuracy Horizontal Accuracy.
 @param verticalAccuracy Vertical Accuracy.
 */
+(void)setLocation:(double)latitude longitude:(double)longitude horizontalAccuracy:(float)horizontalAccuracy verticalAccuracy:(float)verticalAccuracy;

/** Set the user's location.
 @param description The location's description.
 */
+(void)setLocationDescription:(NSString*)description;

/****************
 Privacy Control
 ****************/
 
/** Mark a view as sensitive, to ensure it is not displayed in videos.
 @param view A UIView that contains sensitive information.
 */
+(void)markViewAsSensitive:(UIView*)view;

/** Mark a layer as sensitive, to ensure it is not displayed in videos.
 @param layer A CALayer that contains sensitive information.
 @param view the UIView which contains the sensitive layer.
 */
+(void)markLayerAsSensitive:(CALayer*)layer inView:(UIView *)parentView;

/** Unmark a view as sensitive, so it will be displayed in videos. Unmarking a view will also prevent future auto-detected views from being masked.
 @param view A UIView that no longer contains sensitive information.
 */
+(void)unmarkViewAsSensitive:(UIView*)view;

/** Unmark a layer as sensitive, so it will be displayed in videos.
 @param layer A CALayer that no longer contains sensitive information.
 @param view the UIView which contains the layer.
 */
+(void)unmarkLayerAsSensitive:(CALayer *)layer inView:(UIView *)parentView;

/*********************
3rd Party Integration
**********************/ 
/** Generate a unique ID for an external 3rd party system.
This method should be usually called right after the start: method.
@param systemName The 3rd party system name (ie: "Adobe")
@param isPersistent Whether the identifier should be persistent across sessions.
*/
+(NSString *)generate3rdPartyID:(NSString *)systemName persistent:(BOOL)isPersistent;

/** Set the ID of an external 3rd party system.
This method should be usually called right after the start: method.
@param systemName The 3rd party system name (ie: "Adobe")
@param isPersistent Whether the identifier should be persistent across sessions.
*/
+(void)set3rdPartyID:(NSString *)externalID forSystem:(NSString *)systemName persistent:(BOOL)isPersistent;

/******************************
 WebView Javascript Interface
 *****************************/
/**
 You can call Appsee methods from within a WebView, using Javascript. To do so, call this method,
 and then an 'Appsee' object will be available in Javascript, exposing the native methods.
 @param webView A WKWebView or UIWebView object.
 */
+(void)installJavascriptInterface:(UIView*)webView;

/*********
 Delegate
 *********/
/** Set a delegate to receive appsee notifications
 * @param delegate an instance of AppseeDelegate
 */
+(void)setDelegate:(id<AppseeDelegate>)delegate;

/******
 OpenGL
 ******/

/** Mark the starting of the render loop. This method is optional and should be called only if calling appendGLFrame: alone results in empty videos.
 This should be called right after binding a render buffer, and before drawing object onto it. After drawing the objects, call presentRenderBuffer:.
 */
+(void)startRenderLoop;

/*! The following methods append the OpenGL render buffer to the video. Should be called right before calling 'presentRenderbuffer:'.
 * If you have more than one render buffer, bind it first using glBindRenderbuffer.
 * @param glView The UIView on which the OpenGL scene is presented.
 * @param includeUIKitElements This parameter states whether UIKit elements should be included in the output.
 */
+(void)appendGLFrame:(UIView *)glView;
+(void)appendGLFrame:(UIView *)glView includeUIKitElements:(BOOL)includeUIKit;

+(void)appendGLFrameUnity:(UIView *)glView;
+(void)appendGLFrameUnity:(UIView *)glView includeUIKitElements:(BOOL)includeUIKit;


@end


/************************
 AppseeDelegate Protocol
************************/
@protocol AppseeDelegate <NSObject>

@optional
-(BOOL)appseeSessionStarting;

@optional
-(void)appseeSessionStarted:(NSString *)sessionId videoRecorded:(BOOL)isVideoRecorded;

@optional
-(BOOL)appseeSessionEnding:(NSString *)sessionId;

@optional
-(void)appseeSessionEnded:(NSString *)sessionId;

@optional
-(NSString *)appseeScreenDetected:(NSString *)screenName;

@end

@compatibility_alias Appsee AppseeWFRN;
