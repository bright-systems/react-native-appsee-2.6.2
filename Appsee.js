'use strict';
var { Platform, NativeModules, findNodeHandle, InteractionManager } = require('react-native');
var AppseeBridge = NativeModules.Appsee;


class Appsee {

    static start(apiKey) {
        AppseeBridge.start(apiKey);
    }

    static stop() {
        AppseeBridge.stop();
    }


    static pause() {
        AppseeBridge.pause();
    }


    static resume() {
        AppseeBridge.resume();
    }


    static finishSession(verifyBackground, shouldUpload) {
        if (verifyBackground == null || shouldUpload == null) {
            console.log('appsee : finishSession params are invalid');
            return;
        }
        AppseeBridge.finishSession(verifyBackground, shouldUpload);
    }


    static forceNewSession() {
        AppseeBridge.forceNewSession();
    }


    static upload() {
        AppseeBridge.upload();
    }


    static addEvent(eventName, properties) {
        if (!eventName) {
            console.log('appsee : addEvent params are invalid');
            return;
        }
        properties = (properties == null) ? {} : properties;
        AppseeBridge.addEvent(eventName, properties);
    }


    static startScreen(screenName) {
        if (!screenName) {
            console.log('appsee : startScreen params are invalid');
            return;
        }
        AppseeBridge.startScreen(screenName);
    }


    static setUserId(userId) {
        if (!userId) {
            console.log('appsee : setUserId params are invalid');
            return;
        }
        AppseeBridge.setUserId(userId);
    }

    static setUserProperties(properties) {
        if (!properties) {
            console.log('appsee: setUserProperties params are invalid');
            return;
        }
        AppseeBridge.setUserProperties(properties);
    }

    static incUserProperty(propertyName, value)
    {
        if (!propertyName || value == null) {
            console.log('appsee: incUserProperty params are invalid');
            return;
        }
        AppseeBridge.incUserProperty(propertyName, value);
    }

    static appendToUserProperty(propertyName, item) {
        if (!propertyName || !item) {
            console.log('appsee: appendToUserProperty params are invalid');
            return;
        }
        AppseeBridge.appendToUserProperty(propertyName, item);
    }

    static removeUserProperty(propertyName) {
        if (!propertyName) {
            console.log('appsee: removeUserProperty params are invalid');
            return;
        }
        AppseeBridge.removeUserProperty(propertyName);
    }

    static setLocation(latitude, longitude, horizontalAccuracy, verticalAccuracy) {
        if (latitude == null ||
            longitude == null ||
            horizontalAccuracy == null ||
            verticalAccuracy == null) {
            console.log('appsee : setLocation params are invalid');
            return;
        }
        AppseeBridge.setLocation(latitude, longitude, horizontalAccuracy, verticalAccuracy);
    }

    static setLocationDescription(description) {
        if (!description) {
            console.log('appsee : setLocationDescription can\'t be empty');
            return;
        }
        AppseeBridge.setLocationDescription(description);
    }

    static setOptOutStatus(status) {
        if (status == null) {
            console.log('appsee : setOptOutStatus params are invalid');
            return;
        }
        AppseeBridge.setOptOutStatus(status);
    }    

    static markViewAsSensitive(ref) {
        if (ref == null) {
            console.log('appsee : Can\'t mark a null ref as sensitive (are you sure the component has a ref?)');
            return;
        }

        AppseeBridge.markViewAsSensitive(findNodeHandle(ref));
    }

    static unmarkViewAsSensitive(ref) {
        if (ref == null) {
            console.log('appsee : Can\'t unmark a null ref as sensitive (are you sure the component has a ref?)');
            return;
        }
        
        AppseeBridge.unmarkViewAsSensitive(findNodeHandle(ref));
    }

    static generate3rdPartyID(systemName, isPersistent) {
        if (!systemName) {
            console.log('appsee : generate3rdPartyID params are invalid');
            return;
        }
        
        AppseeBridge.generate3rdPartyID(systemName, isPersistent);
    }

    static set3rdPartyID(externalID, systemName, isPersistent) {
        if (!externalID || !systemName) {
            console.log('appsee : set3rdPartyID params are invalid');
            return;
        }
        
        AppseeBridge.set3rdPartyID(externalID, systemName, isPersistent);
    }
    
    static addScreenAction(actionName) {
        if (!actionName) {
            console.log('appsee : addScreenAction params are invalid');
            return;
        }
        AppseeBridge.addScreenAction(actionName);
    }

    static deleteCurrentUserData() {
        AppseeBridge.deleteCurrentUserData();
    }

    static setDebug(isDebug) {
        AppseeBridge.setDebug(isDebug);
    }

}
module.exports = Appsee;
