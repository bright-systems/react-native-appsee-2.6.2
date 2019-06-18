#import "RNAppsee.h"
#import "Appsee.h"
#import <objc/runtime.h>
#import "AppseeReactNativeExtension.h"

@implementation RNAppsee

@synthesize bridge = _bridge;

RCT_EXPORT_MODULE(Appsee)

RCT_EXPORT_METHOD(start: (NSString *) apiKey){
    dispatch_async(dispatch_get_main_queue(), ^{
        [AppseeReactNativeExtension install];
        [Appsee performSelector:@selector(appendSDKType:) withObject:@"rn"];
        [Appsee start: apiKey];
    });
}

RCT_EXPORT_METHOD(stop){
    [Appsee stop];
}

RCT_EXPORT_METHOD(pause){
    [Appsee pause];
}

RCT_EXPORT_METHOD(resume){
    [Appsee resume];
}

RCT_EXPORT_METHOD(finishSession: (BOOL) verifyBackground upload: (BOOL) shouldUpload){
    [Appsee finishSession: verifyBackground upload: shouldUpload];
}

RCT_EXPORT_METHOD(forceNewSession){
    [Appsee forceNewSession];
}

RCT_EXPORT_METHOD(upload){
    [Appsee upload];
}

RCT_EXPORT_METHOD(addEvent: (NSString *) eventName withProperties: (NSDictionary *) properties){
    [Appsee addEvent: eventName withProperties: properties];
}

RCT_EXPORT_METHOD(startScreen: (NSString *) screenName){
    [Appsee startScreen: screenName];
}

RCT_EXPORT_METHOD(addScreenAction: (NSString *) actionName){
    [Appsee addScreenAction: actionName];
}

RCT_EXPORT_METHOD(setUserId: (NSString *) userID){
    [Appsee setUserID: userID];
}

RCT_EXPORT_METHOD(setUserProperty:(NSString*)propertyName withValue:(id)propertyValue){
    [Appsee setUserProperty:propertyName withValue:propertyValue];
}

RCT_EXPORT_METHOD(setUserProperties:(NSDictionary*)userProperties){
    [Appsee setUserProperties:userProperties];
}

RCT_EXPORT_METHOD(incUserProperty:(NSString *)propertyName incrementBy:(NSNumber *)value){
    [Appsee incUserProperty:propertyName incrementBy:value];
}

RCT_EXPORT_METHOD(appendToUserProperty:(NSString *)propertyName listItem:(NSString *)item){
    [Appsee appendToUserProperty:propertyName listItem:item];
}

RCT_EXPORT_METHOD(removeUserProperty:(NSString*)propertyName){
    [Appsee removeUserProperty:propertyName];
}

RCT_EXPORT_METHOD(setLocation: (double) latitude
                  atLongitude: (double) longtitude
                  horizontalAccuracy: (float) horizontalAccuracy
                  verticalAccuracy: (float) varticalAccuracy){
    [Appsee setLocation: latitude
              longitude:longtitude
     horizontalAccuracy:horizontalAccuracy
       verticalAccuracy:varticalAccuracy];
}

RCT_EXPORT_METHOD(setLocationDescription: (NSString *) description){
    [Appsee setLocationDescription: description];
}

RCT_EXPORT_METHOD(setOptOutStatus: (BOOL) status){
    [Appsee setOptOutStatus: status];
}

RCT_EXPORT_METHOD(deleteCurrentUserData){
    [Appsee deleteCurrentUserData];
}


RCT_EXPORT_METHOD(generate3rdPartyID: (NSString *) systemName persistent: (BOOL) isPersistent){
    [Appsee generate3rdPartyID:systemName persistent:isPersistent];
}

RCT_EXPORT_METHOD(set3rdPartyID:(NSString *)externalID forSystem:(NSString *)systemName persistent:(BOOL)isPersistent){
    [Appsee set3rdPartyID:externalID forSystem:systemName persistent:isPersistent];
}

RCT_EXPORT_METHOD(markViewAsSensitive: (nonnull NSNumber *) tag){
    dispatch_async(dispatch_get_main_queue(), ^{
        UIView* view = [self.bridge.uiManager viewForReactTag:tag];
        [Appsee markViewAsSensitive:view];
    });
}

RCT_EXPORT_METHOD(unmarkViewAsSensitive: (nonnull NSNumber *) tag){
    dispatch_async(dispatch_get_main_queue(), ^{
        UIView* view = [self.bridge.uiManager viewForReactTag:tag];
        [Appsee unmarkViewAsSensitive:view];
    });
}

RCT_EXPORT_METHOD(setDebug: (BOOL) isDebug){
    [Appsee setDebugToNSLog:isDebug];
}

@end
