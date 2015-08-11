var resourceJSON = "";

function getUrl() {
    "use strict";
    

    var docUrl = document.referrer;
    var urlResult = docUrl;
    var beginIndex = docUrl.indexOf('#') + 1;

    
    if (docUrl.indexOf("file://", beginIndex) == -1) {
        
        var protocolEndIndex = docUrl.indexOf("://", beginIndex);

        
        var endIndex = docUrl.indexOf("/", protocolEndIndex + 3);

        urlResult = docUrl.substring(beginIndex, endIndex);
    }
    return urlResult;
}

function isExternalUrlSafeForNavigation(urlStr) {
    "use strict";
    var regEx = new RegExp("^(http(s?)|ftp|file)://", "i");
    return regEx.exec(urlStr);
}

function clickRefresh() {
    "use strict";
    var currentLocation = document.location.href;
    var poundIndex = currentLocation.indexOf('#');

    if (poundIndex != -1 && poundIndex + 1 < currentLocation.length && isExternalUrlSafeForNavigation(currentLocation.substring(poundIndex + 1))) {
        window.location.replace(currentLocation.substring(poundIndex + 1));
    }
}

function clickSearch() {
    "use strict";
    var currentLocation = document.location.href;
    var poundIndex = currentLocation.indexOf('#');

    if (poundIndex != -1 && poundIndex + 1 < currentLocation.length && isExternalUrlSafeForNavigation(currentLocation.substring(poundIndex + 1))) {
        window.open('http://www.bing.com/search?q=' + currentLocation.substring(poundIndex + 1));
    }
}

function getNavigationURL() {
    "use strict";
    var currentLocation = document.location.href;
    var poundIndex = currentLocation.indexOf('#');
    var possibleNavigationURL = currentLocation.substring(poundIndex + 1);

    if (poundIndex != -1 && poundIndex + 1 < currentLocation.length && isExternalUrlSafeForNavigation(possibleNavigationURL)) {
        return possibleNavigationURL;
    } else {
        return '';
    }
}

function isMergedErrorFile() {
    "use strict";
    var url = document.location.href.toLowerCase();
    
    var localAnchor = url.indexOf("#");
    url = url.substring(0, (localAnchor == -1) ? url.length : localAnchor);

    var query = url.indexOf("?");
    url = url.substring(0, (query == -1) ? url.length : query);

    return url.indexOf("errorpages.html", url.lastIndexOf("/") + 1) >= 0;
}

function getErrorCodeFromQuery() {
    "use strict";
    var errorCode = '';
    var errorQueryKey = "error=";

    var query = document.location.search;
    var errorQueryStart = query.indexOf(errorQueryKey);
    if (errorQueryStart > 0) {
        var ampersandStart = query.indexOf("&", errorQueryStart);
        if (ampersandStart > 0) {
            errorCode = query.substring(errorQueryStart + errorQueryKey.length, ampersandStart);
        } else {
            errorCode = query.substring(errorQueryStart + errorQueryKey.length);
        }
    }

    return errorCode;
}

function showErrorPage() {
    "use strict";
    if (isMergedErrorFile()) {
        setWebpageUrl();

        var errorCode = getErrorCodeFromQuery();
        setDocumentTitle(errorCode);
        initializeErrorCodeDiv(errorCode);
        initializeContinueLink(errorCode);
        hideHomepageLinks();

        
        document.getElementById(errorCode).style.display = "inline";
    }
}

function goToLocalizedErrorPage() {
    "use strict";
     showErrorPage();
}

function setWebpageUrl() {
    "use strict";
    var url = getUrl();
    var urlElements = document.getElementsByClassName("webpageURL");
    for (var i = 0; i < urlElements.length; i++) {
        urlElements[i].textContent = url;
    }
}

function setDocumentTitle(errorCode) {
    "use strict";
    
    if (errorCode == 3) { document.title = L_Syntax_Title_TEXT; }
    else if (errorCode == 4) { document.title = L_NavCancel_Title_TEXT; }
    else if (errorCode == 5) { document.title = L_PhishingSite_Title_TEXT; }
    else if (errorCode == 6) { document.title = L_InvalidCert_Title_TEXT; }
    else if (errorCode == 7) { document.title = L_SSLNavCancel_Title_TEXT; }
    else if (errorCode == 8) { document.title = L_UnknownProtocol_Title_TEXT; }
    else if (errorCode == 9) { document.title = L_ForbidFraming_Title_TEXT; }
    else if (errorCode == 10) { document.title = L_ProxyError_Title_TEXT; }
    
    else if (errorCode == 12) { document.title = L_TLSError_Title_TEXT; }
    
    else if (errorCode == 14) { document.title = L_HSTS_Title_TEXT; }
    
    else if (errorCode == 17) { document.title = L_PDF_Title_TEXT; }
    else if (errorCode == 18) { document.title = L_PDF_Title_TEXT; }
    else if (errorCode == 400) { document.title = L_Http_400_Title_TEXT; }
    else if (errorCode == 403) { document.title = L_Http_403_Title_TEXT; }
    else if (errorCode == 404) { document.title = L_Http_404_Title_TEXT; }
    else if (errorCode == 405) { document.title = L_Http_405_Title_TEXT; }
    else if (errorCode == 406) { document.title = L_Http_406_Title_TEXT; }
    else if (errorCode == 408) { document.title = L_Http_408_409_Title_TEXT; }
    else if (errorCode == 409) { document.title = L_Http_408_409_Title_TEXT; }
    else if (errorCode == 410) { document.title = L_Http_410_Title_TEXT; }
    else if (errorCode == 500) { document.title = L_Http_500_Title_TEXT; }
    else if (errorCode == 501) { document.title = L_Http_501_Title_TEXT; }
    else if (errorCode == 505) { document.title = L_Http_501_Title_TEXT; }
}

function initializeErrorCodeDiv(errorCode) {
    "use strict";
    if (errorCode == 1 || errorCode == 2) {
        
        initializeDnsError();
    }
}

function initializeContinueLink(errorCode) {
    "use strict";
    if (errorCode == 6) {
        document.getElementById('continueLink').href = getNavigationURL();
    }
}


function hideHomepageLinks() {
    "use strict";
    getParentRowContainer('invalidcert_gohome').style.display = "none";
    getParentRowContainer('hstscerterror_gohome').style.display = "none";
    getParentRowContainer('acr_error_gohome').style.display = "none";
    getParentRowContainer('acr_depnx_error_gohome').style.display = "none";
}


function getParentRowContainer(elementId) {
    "use strict";
    var ancestorCount = 0;
    var originalElement = document.getElementById(elementId);
    var element = originalElement;
    for (var ancestors = 0; ancestors < 4 && element; ancestors++) {
        if (element.tagName.toLowerCase() === "tr"  ||
            element.tagName.toLowerCase() === "li") {
            return element;
        }
        element = element.parentElement;
    }
    return originalElement;
}

function initializeDnsError() {
    "use strict";
    
    checkConnectionForDnsError();

    
    if (document.addEventListener) {
        addEventListener("offline", reportConnectionEvent, false);
    }
    else {
        attachEvent("onoffline", reportConnectionEvent);
    }

    
    document.body.ononline = reportConnectionEvent;
    document.body.onoffline = reportConnectionEvent;
}

function checkConnectionForDnsError() {
    "use strict";
    var notConnected = document.getElementById("NotConnected");
    var pageUnavailable = document.getElementById("PageUnavailable");

    if (navigator.onLine) { 
        document.title = L_Unavailable_Title_TEXT;

        notConnected.style.display = "none";
        pageUnavailable.style.display = "";
    }
    else { 
        document.title = L_Disconnected_Title_TEXT;

        notConnected.style.display = "";
        pageUnavailable.style.display = "none";
    }
}

function reportConnectionEvent(e) {
    "use strict";
    if (!e) e = window.event;

    if ('online' == e.type) {
        
        setTimeout("clickRefresh()", 1000);
    }
    else {
        checkConnectionForDnsError();
    }
}