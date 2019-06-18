package com.appsee.reactnative;

import android.app.Activity;
import android.view.View;
import com.appsee.Appsee;
import com.facebook.react.ReactPackage;
import com.facebook.react.bridge.JavaScriptModule;
import com.facebook.react.bridge.NativeModule;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.ReadableMap;
import com.facebook.react.bridge.ReadableMapKeySetIterator;
import com.facebook.react.bridge.ReadableArray;
import com.facebook.react.uimanager.ViewManager;
import com.facebook.react.uimanager.NativeViewHierarchyManager;
import com.facebook.react.uimanager.UIBlock;
import com.facebook.react.uimanager.UIManagerModule;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import android.util.Log;

public class AppseeReactPackage implements ReactPackage {

    public AppseeReactPackage() {}

    @Override
    public List<NativeModule> createNativeModules(ReactApplicationContext reactContext) {
        List<NativeModule> modules = new ArrayList<>();

        modules.add(new AppseeModule(reactContext));

        return modules;
    }

    // Deprecated RN 0.47
    public List<Class<? extends JavaScriptModule>> createJSModules() {
        return Collections.emptyList();
    }

    @Override
    public List<ViewManager> createViewManagers(ReactApplicationContext reactContext) {
        return Collections.emptyList();
    }


    private class AppseeModule extends ReactContextBaseJavaModule {

        AppseeModule(ReactApplicationContext reactContext) {
            super(reactContext);
        }

        @Override
        public String getName() {
            return "Appsee";
        }

        @ReactMethod
        public void start(String apiKey) {
            Appsee.appendSDKType("rn");
            Appsee.setSkipStartValidation(true);
            Appsee.start(apiKey);
        }

        @ReactMethod
        public void stop() {
            Appsee.stop();
        }

        @ReactMethod
        public void pause() {
            Appsee.pause();
        }

        @ReactMethod
        public void resume() {
            Appsee.resume();
        }

        @ReactMethod
        public void finishSession(boolean verifyBackground, boolean shouldUpload) {
            Appsee.finishSession(verifyBackground, shouldUpload);
        }

        @ReactMethod
        public void forceNewSession() {
            Appsee.forceNewSession();
        }

        @ReactMethod
        public void upload() {
            Appsee.upload();
        }

        @ReactMethod
        public void addEvent(String eventName, ReadableMap properties){
            if(properties == null) {
                Appsee.addEvent(eventName);
            } else {
                Appsee.addEvent(eventName, toHashMap(properties));
            }
        }

	    // Taken from react source code on github to support older react-native versions (<0.46), before it was implemented in react-native itself
	    // https://github.com/facebook/react-native/blob/master/ReactAndroid/src/main/java/com/facebook/react/bridge/ReadableNativeMap.java
	    public HashMap<String, Object> toHashMap(ReadableMap readableMap)
	    {
		    ReadableMapKeySetIterator iterator = readableMap.keySetIterator();
		    HashMap<String, Object> hashMap = new HashMap<>();

		    while (iterator.hasNextKey())
		    {
			    String key = iterator.nextKey();
			    switch (readableMap.getType(key))
			    {
				    case Null:
					    hashMap.put(key, null);
					    break;
				    case Boolean:
					    hashMap.put(key, readableMap.getBoolean(key));
					    break;
				    case Number:
					    hashMap.put(key, readableMap.getDouble(key));
					    break;
				    case String:
					    hashMap.put(key, readableMap.getString(key));
					    break;
				    case Map:
					    hashMap.put(key, toHashMap(readableMap.getMap(key)));
					    break;
				    case Array:
					    hashMap.put(key, toArrayList(readableMap.getArray(key)));
					    break;
				    default:
					    throw new IllegalArgumentException("Could not convert object with key: " + key + ".");
			    }
		    }
		    return hashMap;
	    }

	    // Taken from react source code on github to support older react-native versions (<0.46), before it was implemented in react-native itself
	    // https://github.com/facebook/react-native/blob/master/ReactAndroid/src/main/java/com/facebook/react/bridge/ReadableNativeArray.java
	    public ArrayList<Object> toArrayList(ReadableArray readableArray)
	    {
		    ArrayList<Object> arrayList = new ArrayList<>();

		    for (int i = 0; i < readableArray.size(); i++)
		    {
			    switch (readableArray.getType(i))
			    {
				    case Null:
					    arrayList.add(null);
					    break;
				    case Boolean:
					    arrayList.add(readableArray.getBoolean(i));
					    break;
				    case Number:
					    arrayList.add(readableArray.getDouble(i));
					    break;
				    case String:
					    arrayList.add(readableArray.getString(i));
					    break;
				    case Map:
					    arrayList.add(toHashMap(readableArray.getMap(i)));
					    break;
				    case Array:
					    arrayList.add(toArrayList(readableArray.getArray(i)));
					    break;
				    default:
					    throw new IllegalArgumentException("Could not convert object at index: " + i + ".");
			    }
		    }
		    return arrayList;
	    }
        @ReactMethod
        public void startScreen(String screenName) {
            Appsee.startScreen(screenName);
        }

        @ReactMethod
        public void setUserId(String userId) {
            Appsee.setUserId(userId);
        }

        @ReactMethod
        public void setLocation(double latitude, double longitude,
            float horizontalAccuracy, float verticalAccuracy) {
            Appsee.setLocation(latitude, longitude, horizontalAccuracy, verticalAccuracy);
        }

        @ReactMethod
        public void setLocationDescription(String description) {
            Appsee.setLocationDescription(description);
        }

        @ReactMethod
        public void addScreenAction(String actionName) {
            Appsee.addScreenAction(actionName);
        }

        @ReactMethod
        public void setOptOutStatus(boolean status) {
            Appsee.setOptOutStatus(status);
        }

        @ReactMethod
        public void deleteCurrentUserData() {
            Appsee.deleteCurrentUserData();
        }

	    @ReactMethod
	    public void generate3rdPartyID(String systemName, boolean isPersistent) {
		    Appsee.generate3rdPartyId(systemName, isPersistent);
	    }

	    @ReactMethod
	    public void set3rdPartyID(String externalId, String systemName, boolean isPersistent) {
		    Appsee.set3rdPartyId(systemName, externalId, isPersistent);
	    }

	    @ReactMethod
        public void markViewAsSensitive(final int id) {
		    UIManagerModule uiManager = getReactApplicationContext().getNativeModule(UIManagerModule.class);
		    uiManager.addUIBlock(new UIBlock()
		    {
			    @Override
			    public void execute(NativeViewHierarchyManager nativeViewHierarchyManager)
			    {
                    try
                    {
                        View view = nativeViewHierarchyManager.resolveView(id);
                        
                        if (view != null)
                            Appsee.markViewAsSensitive(view);
                    }
                    catch(Exception e)
                    {
                        Log.d("Appsee", "Appsee markViewAsSensitive: can't find view by id: " + id);
                    }
			    }
		    });
        }

        @ReactMethod
        public void unmarkViewAsSensitive(final int id) {
	        UIManagerModule uiManager = getReactApplicationContext().getNativeModule(UIManagerModule.class);
	        uiManager.addUIBlock(new UIBlock()
	        {
		        @Override
		        public void execute(NativeViewHierarchyManager nativeViewHierarchyManager)
		        {
                    try
                    {
                        View view = nativeViewHierarchyManager.resolveView(id);
                        
                        if (view != null)
                            Appsee.unmarkViewAsSensitive(view);
                    }
                    catch(Exception e)
                    {
                        Log.d("Appsee", "Appsee unmarkViewAsSensitive: can't find view by id: " + id);
                    }
		        }
	        });
        }

        @ReactMethod
        public void setDebug(boolean isDebug) {
            Appsee.setDebugToLogcat(isDebug);
        }

	    @ReactMethod
	    public void setUserProperties(ReadableMap userProperties){
		    Appsee.setUserProperties(toHashMap(userProperties));
	    }

	    @ReactMethod
	    public void incUserProperty(String propertyName, double value){
		    Appsee.incUserProperty(propertyName, value);
	    }

	    @ReactMethod
	    public void appendToUserProperty(String propertyName, String item){
		    Appsee.appendToUserProperty(propertyName, item);
	    }

	    @ReactMethod
	    public void removeUserProperty(String propertyName){
		    Appsee.removeUserProperty(propertyName);
	    }
    }
}
