var AnyChatSDK = function() {
    var PeerConnection = (window.PeerConnection || window.webkitPeerConnection00 || window.webkitRTCPeerConnection || window.mozRTCPeerConnection);
    var URL = (window.URL || window.webkitURL || window.msURL || window.oURL);
    var getUserMedia = (navigator.getUserMedia || navigator.webkitGetUserMedia || navigator.mozGetUserMedia || navigator.msGetUserMedia);
    var nativeRTCIceCandidate = (window.mozRTCIceCandidate || window.RTCIceCandidate);
    var nativeRTCSessionDescription = (window.mozRTCSessionDescription || window.RTCSessionDescription); // order is very important: "RTCSessionDescription" defined in Nighly but useless
    var moz = !!navigator.mozGetUserMedia;
    var iceServer = {
        "iceServers": [{
            "url": "stun:stun.l.google.com:19302"
        }]
    };

    function EventEmitter() {
        this.events = {};
    }
    //���¼�����
    EventEmitter.prototype.on = function(eventName, callback) {
        this.events[eventName] = this.events[eventName] || [];
        this.events[eventName].push(callback);
    };
    //�����¼�����
    EventEmitter.prototype.emit = function(eventName, _) {
        var events = this.events[eventName],
            args = Array.prototype.slice.call(arguments, 1),
            i, m;

        if (!events) {
            return;
        }
        for (i = 0, m = events.length; i < m; i++) {
            events[i].apply(null, args);
        }
    };


    /**********************************************************/
    /*                                                        */
    /*                   �����ŵ���������                     */
    /*                                                        */
    /**********************************************************/


    /*******************��������*********************/
    function anychat() {		
		this.localStatus = {socketConnect:false, sdkauthpass:"",
							loginuser:"", loginpass:"", loginparam:0, 
							roomid:-1, roomname:"", roompass:"", roomparam:0,
							selfuserid:-1};
							
		// ���ӷ������ɹ�֮ǰ�Ĳ�����������
		this.sdkoptionData = {};
		// �û�������Ϣ
		this.userInfoData = {};
		// �û�������Ϣ
		this.friendInfoData = {};
		// �û�������Ϣ
		this.groupInfoData = {};
		// ҵ���������
		this.objectInfoData = {};
		// �����û�����
		this.roomusers = [];
		// ���еȴ�ʱ�������
		this.queueWaitSeconds = 0;
		this.queueWaitTimer = -1;
			
        //����media stream
        this.localMediaStream = null;
		this.localVideoObject = null;
		this.remoteMediaStream = null;
		this.remoteVideoObject = null;
		
        //����WebSocket����
        this.socket = null;
        //����socket��id���ɺ�̨����������
        this.me = null;
        //���������뱾��������peer connection�� ��Ϊsocket id��ֵΪPeerConnection����
        this.peerConnections = {};
        //���������뱾�����ӵ�socket��id
        this.connections = [];
        //��ʼʱ��Ҫ�������ӵ���Ŀ
        this.numStreams = 0;
        //��ʼʱ�Ѿ����ӵ���Ŀ
        this.initializedStreams = 0;
    }
    //�̳����¼����������ṩ���¼��ʹ����¼��Ĺ���
    anychat.prototype = new EventEmitter();


	function addlog(funcname, message) {
	console.warn(funcname);
	if(message.length)
		console.log("\t " + message);
	}
	
	function clearAllStatus(){
		clearRoomStatus();
		this.anychat.userInfoData = {};
		this.anychat.friendInfoData = {};
		this.anychat.groupInfoData = {};
		this.anychat.objectInfoData = {};
		this.anychat.localStatus.loginuser = "";
		this.anychat.localStatus.selfuserid = -1;
	}
	
	function clearRoomStatus(){
		this.anychat.roomusers = [];
		this.anychat.localStatus.roomid = -1;
		this.anychat.localStatus.roomname = "";
	}


    /*************************���������Ӳ���***************************/
	
	anychat.prototype.InitSDK = function(dwFlags) {
		var that = this;
		this.on('_notifyMessage', function(data) {
			var ls = that.localStatus;
			if(data.event == WM_GV_CONNECT) {
				if(data.lParam == 0 && ls.loginuser.length) {
					that.socket.sendCommand("login", {"username":ls.loginuser, "password":ls.loginpass, "param":ls.loginparam, "sdkauthpass":ls.sdkauthpass});
				}
			} else if(data.event == WM_GV_LOGINSYSTEM) {
				if(data.lParam == 0) {
					that.createStream();
					that.localStatus.selfuserid = data.wParam;
					// ��û��ͬ���Ĳ������ô���������
					for(var optname in that.sdkoptionData) {
						that.socket.sendCommand(that.sdkoptionData[optname].command, that.sdkoptionData[optname].param);
					}
					// �Զ����뷿��
					if(that.localStatus.roomid != -1) {
						that.socket.sendCommand("enterroom", {"roomid":ls.roomid, "password":ls.roompass, "param":ls.roomparam});
					} else if(that.localStatus.roomname.length) {
						that.socket.sendCommand("enterroomex", {"roomname":ls.roomname, "password":ls.roompass});
					}
				}
			} else if(data.event == WM_GV_ENTERROOM) {
				var userid = data.wParam;
				var bEnter = data.lParam;
				if(bEnter) {
					that.roomusers.push(userid);
				} else {
					for(var i=0; i<that.roomusers; i++) {
						if(that.roomusers[i] == userid) {
							delete that.roomusers[i];
							break;
						}
					}
				}
			}
			that.emit("OnNotifyMessage", data.event, data.wParam, data.lParam);
		});
		// �յ���Ƶ�����¼�֪ͨ
		this.on('_videoCallEvent', function(data) {
			that.emit("OnVideoCallEvent", data.event, data.userid, data.errorcode, data.flags, data.param, data.userstr);
		});
		// �յ�͸��ͨ���¼�֪ͨ
		this.on('_transBufferEvent', function(data) {
			that.emit("OnTransBuffer", data.userid, data.buf, data.buf.length);
		});
		// �յ����������¼�֪ͨ
		this.on('_textMessageEvent', function(data) {
			that.emit("OnTextMessage", data.fromuserid, data.touserid, data.secret, data.msgbuf, data.msgbuf.length);
		});
		// �յ��û��������ݣ����浽json������ȥ
		this.on('_userBaseInfo', function(data) {
			var info = {"nickname":data.nickname, "level":data.level, "internetip":data.internetip};
			that.userInfoData[data.userid] = info
		});
		// �յ��û��������ݣ����浽json������ȥ
		this.on('_userFriendInfo', function(data) {
			var info = {"groupid":data.groupid, "status":data.status, "t1":data.t1, "t2":data.t2, "t3":data.t3, "t4":data.t4, "t5":data.t5, "t6":data.t6, "t7":data.t7, "t8":data.t8, "t9":data.t9, "t10":data.t10};
			that.friendInfoData[data.userid] = info
		});
		// �յ��û��������ݣ����浽json������ȥ
		this.on('_groupBaseInfo', function(data) {
			var info = {"groupname":data.groupname};
			that.groupInfoData[data.groupid] = info
		});		
		// �յ������û��б������±�������
		this.on('_roomUserList', function(data) {
			that.roomusers = [];
			var useridlist = data.useridlist.split(";");
			for(i=0; i<useridlist.length; i++) {
				if(useridlist[i] != "")
					that.roomusers.push(useridlist[i]);
			}
		});
		// �յ�ҵ��������ݣ����浽json������ȥ
		this.on('_objectBaseInfo', function(data) {
			var status = {};
			if(typeof that.objectInfoData[data.objecttype + "_" + data.objectid] != "undefined")
				status = that.objectInfoData[data.objecttype + "_" + data.objectid].status;
			var info = {"objecttype":data.objecttype, "objectid":data.objectid, "flags":data.flags, "objectname":data.objectname, "priority":data.priority, "attribute":data.attribute, "inttag":data.inttag, "objectdesc":data.objectdesc, "strtag":data.strtag, "status":status};
			that.objectInfoData[data.objecttype + "_" + data.objectid] = info;
		});
		// �յ�ҵ�����״̬��Ϣ�����浽json������ȥ
		this.on('_objectStatus', function(data) {
			for(var i in that.objectInfoData) {
				if(that.objectInfoData[i].objecttype == data.objecttype && that.objectInfoData[i].objectid == data.objectid) {
					for(var k in data) {
						if(k == "objecttype" || k == "objectid")
							continue;
						that.objectInfoData[i].status[k] = data[k];
					}
					break;
				}
			}
		});
		// �յ�ҵ������첽�¼�֪ͨ
		this.on('_objectEvent', function(data) {
			if(data.event == ANYCHAT_QUEUE_EVENT_ENTERRESULT) {
				that.queueWaitSeconds = 0;
				if(that.queueWaitTimer == -1) {
					that.queueWaitTimer = setInterval(function () {
						that.queueWaitSeconds++;
					}, 1000);
				}
			} else if(data.event == ANYCHAT_QUEUE_EVENT_LEAVERESULT) {
				if(that.queueWaitTimer != -1)
					clearInterval(that.queueWaitTimer);
			}
			that.emit("OnObjectEvent", data.objecttype, data.objectid, data.event, data.param1, data.param2, data.param3, data.param4, data.strparam);
		});
		
	}


    //���������ŵ����ŵ�Ϊwebsocket
    anychat.prototype.Connect = function(server, port) {
        var socket, that = this;
		var webSocketPort = (parseInt(port) + 2);;
		var wsurl = "ws://" + server + ":" + webSocketPort;
		if (typeof MozWebSocket != "undefined") {
			socket = this.socket = new MozWebSocket(wsurl, "anychat-protocol");
		} else {
			socket = this.socket = new WebSocket(wsurl, "anychat-protocol");
		}
		
		socket.sendCommand = function(name, data) {
			socket.send(JSON.stringify({
                "eventName": name,
                "data": data
            }));
		}
		
        socket.onopen = function() {
			socket.sendCommand("connect", {"os":0, "host":server, "port":webSocketPort});
			that.emit("socket_opened", socket);
			that.localStatus.socketConnect = true;
        };

        socket.onmessage = function(message) {
			//addlog("socket.onmessage", message.data);
            var json = JSON.parse(message.data);
            if (json.eventName) {
                that.emit(json.eventName, json.data);
            } else {
                that.emit("socket_receive_message", socket, json);
            }
        };

        socket.onerror = function(error) {
			if(that.localStatus.socketConnect)
				that.emit("OnNotifyMessage", WM_GV_LINKCLOSE, 0, 101);
			else
				that.emit("OnNotifyMessage", WM_GV_CONNECT, 0, 115);
            that.emit("socket_error", error, socket);
			that.localStatus.socketConnect = false;
        };

        socket.onclose = function(data) {
/*          that.localMediaStream.close();
            var pcs = that.peerConnections;
            for (i = pcs.length; i--;) {
                that.closePeerConnection(pcs[i]);
            }
            that.peerConnections = [];
            that.dataChannels = {};
            that.fileChannels = {};
            that.connections = [];
            that.fileData = {};
            that.emit('socket_closed', socket);
*/			
			that.emit("OnNotifyMessage", WM_GV_LINKCLOSE, 0, 0);
			that.socket = null;
			that.localStatus.socketConnect = false;
			clearAllStatus();
        };

        this.on("_ice_candidate", function(data) {
            var candidate = new nativeRTCIceCandidate(data);
            var pc = that.peerConnections[data.userid];
            pc.addIceCandidate(candidate);
            that.emit('get_ice_candidate', candidate);
        });

        this.on('_new_peer', function(data) {
            that.connections.push(data.socketId);
            var pc = that.createPeerConnection(data.socketId),
                i, m;
            pc.addStream(that.localMediaStream);
            that.emit('new_peer', data.socketId);
        });

        this.on('_remove_peer', function(data) {
            var sendId;
            that.closePeerConnection(that.peerConnections[data.socketId]);
            delete that.peerConnections[data.socketId];
            delete that.dataChannels[data.socketId];
            for (sendId in that.fileChannels[data.socketId]) {
                that.emit("send_file_error", new Error("Connection has been closed"), data.socketId, sendId, that.fileChannels[data.socketId][sendId].file);
            }
            delete that.fileChannels[data.socketId];
            that.emit("remove_peer", data.socketId);
        });

        this.on('_offer', function(data) {
            that.receiveOffer(data.socketId, data.sdp);
            that.emit("get_offer", data);
        });

        this.on('_answer', function(data) {
            that.receiveAnswer(data.userid, data.sdp);
            that.emit('get_answer', data);
        });

        this.on('send_file_error', function(error, socketId, sendId, file) {
            that.cleanSendFile(sendId, socketId);
        });

        this.on('receive_file_error', function(error, sendId) {
            that.cleanReceiveFile(sendId);
        });

        this.on('ready', function() {
            that.createPeerConnections();
            that.addStreams();
            that.addDataChannels();
            that.sendOffers();
        });

		return 0;
    };


    /*************************����������*******************************/


    //����������
    anychat.prototype.createStream = function() {
        var that = this;

        var mediaConfig = {video:{mandatory: { minAspectRatio: 1.333, maxAspectRatio: 1.334 },
								optional: [{ maxFrameRate: 15 }, { minWidth: 320 }, { minHeigth: 240 }, { maxWidth: 1280 }, { maxHeigth: 720 }]
							}, audio:true}; 

        if (getUserMedia) {
            getUserMedia.call(navigator, mediaConfig, function(stream) {
                    that.localMediaStream = stream;
					that.localStatus.localMediaStream = stream;
                    if(that.localVideoObject) {
						if (navigator.mozGetUserMedia) {
							that.localVideoObject.mozSrcObject = stream;
							that.localVideoObject.play();
						}
						that.localVideoObject.src = URL.createObjectURL(stream);
						that.localVideoObject.play();
					}
                },
                function(error) {
                    that.emit("stream_create_error", error);
                });
        } else {
            that.emit("stream_create_error", new Error('WebRTC is not yet supported in this browser.'));
        }
    };

    //�����������ӵ����е�PeerConnectionʵ����
    anychat.prototype.addStreams = function() {
        var i, m,
            stream,
            connection;
        for (connection in this.peerConnections) {
            this.peerConnections[connection].addStream(this.localMediaStream);
        }
    };

    //�����󶨵�video��ǩ���������
    anychat.prototype.attachStream = function(stream, domId) {
        var element = document.getElementById(domId);
        if (navigator.mozGetUserMedia) {
            element.mozSrcObject = stream;
            element.play();
        } else {
            element.src = webkitURL.createObjectURL(stream);
        }
        element.src = webkitURL.createObjectURL(stream);
    };


    /***********************���������*******************************/


    //������PeerConnection����Offer��������
    anychat.prototype.sendOffers = function() {
        var i, m,
            pc,
            that = this,
            pcCreateOfferCbGen = function(pc, socketId) {
                return function(session_desc) {
                    pc.setLocalDescription(session_desc);
                    that.socket.send(JSON.stringify({
                        "eventName": "__offer",
                        "data": {
                            "sdp": session_desc,
                            "socketId": socketId
                        }
                    }));
                };
            },
            pcCreateOfferErrorCb = function(error) {
                console.log(error);
            };
        for (i = 0, m = this.connections.length; i < m; i++) {
            pc = this.peerConnections[this.connections[i]];
            pc.createOffer(pcCreateOfferCbGen(pc, this.connections[i]), pcCreateOfferErrorCb);
        }
    };

    //���յ�Offer�����������Ϊ��Ӧ����answer��������
    anychat.prototype.receiveOffer = function(socketId, sdp) {
        var pc = this.peerConnections[socketId];
        this.sendAnswer(socketId, sdp);
    };

    //����answer��������
    anychat.prototype.sendAnswer = function(socketId, sdp) {
        var pc = this.peerConnections[socketId];
        var that = this;
        pc.setRemoteDescription(new nativeRTCSessionDescription(sdp));
        pc.createAnswer(function(session_desc) {
            pc.setLocalDescription(session_desc);
            that.socket.send(JSON.stringify({
                "eventName": "__answer",
                "data": {
                    "socketId": socketId,
                    "sdp": session_desc
                }
            }));
        }, function(error) {
            console.log(error);
        });
    };

    //���յ�answer��������󽫶Է���session����д��PeerConnection��
    anychat.prototype.receiveAnswer = function(userid, sdp) {
		var pc = this.peerConnections[userid];
		var sdc = new nativeRTCSessionDescription();
		sdc.sdp = sdp;
		sdc.type = 'answer';
		pc.setRemoteDescription(sdc);
    };


    /***********************��Ե����Ӳ���*****************************/


    //�����������û����ӵ�PeerConnections
    anychat.prototype.createPeerConnections = function() {
        var i, m;
        for (i = 0, m = this.connections.length; i < m; i++) {
            this.createPeerConnection(this.connections[i]);
        }
    };

    //��������PeerConnection
    anychat.prototype.createPeerConnection = function(dwUserId) {
        var that = this;
		
		var pcOptional={optional:[{DtlsSrtpKeyAgreement: false}]};
		
        var pc = new PeerConnection(iceServer, pcOptional);
        this.peerConnections[dwUserId] = pc;
        pc.onicecandidate = function(evt) {
            if (evt.candidate)
                that.socket.send(JSON.stringify({
                    "eventName": "__ice_candidate",
                    "data": {
                        "label": evt.candidate.sdpMLineIndex,
                        "candidate": evt.candidate.candidate,
                        "userid": dwUserId
                    }
                }));
            that.emit("pc_get_ice_candidate", evt.candidate, dwUserId, pc);
        };

        pc.onopen = function() {
            that.emit("pc_opened", dwUserId, pc);
        };

        pc.onaddstream = function(evt) {
			console.log("onaddstream1");
			that.localStatus.remoteMediaStream = evt.stream;
			if(that.remoteVideoObject) {
				if (navigator.mozGetUserMedia) {
					that.remoteVideoObject.mozSrcObject = evt.stream;
					that.remoteVideoObject.play();
				}
				that.remoteVideoObject.src = URL.createObjectURL(evt.stream);
				that.remoteVideoObject.play();
			}
            that.emit('pc_add_stream', evt.stream, dwUserId, pc);
        };

        pc.ondatachannel = function(evt) {
            that.addDataChannel(dwUserId, evt.channel);
            that.emit('pc_add_data_channel', evt.channel, dwUserId, pc);
        };
        return pc;
    };

    //�ر�PeerConnection����
    anychat.prototype.closePeerConnection = function(pc) {
        if (!pc) return;
        pc.close();
    };
	

	// ��ȡ�汾��Ϣ
	anychat.prototype.GetVersion = function(type) {
		return "2.0.0.0";
	};
	
	anychat.prototype.GetSDKOptionString = function(optname) {
		return "";
	};
	
	anychat.prototype.SetServerAuthPass = function(lpPassword) {
		return 0;
	};
	
	anychat.prototype.Login = function(lpUserName, lpPassword, dwParam){
		var that = this;
		if(that.localStatus.socketConnect) {
			that.socket.sendCommand("login", {"username":lpUserName, "password":lpPassword, "param":parseInt(dwParam), "sdkauthpass":ls.sdkauthpass});
		}
		that.localStatus.loginuser = lpUserName;
		that.localStatus.loginpass = lpPassword;
		that.localStatus.loginparam = dwParam;
		return 0;
	};
	
	anychat.prototype.EnterRoom = function(dwRoomid, lpRoomPass, dwParam) {
		var that = this;
		if(that.localStatus.socketConnect) {
			that.socket.sendCommand("enterroom", {"roomid":parseInt(dwRoomid), "password":lpRoomPass, "param":parseInt(dwParam)});
		}
		that.localStatus.roomid = dwRoomid;
		that.localStatus.roompass = lpRoomPass;
		that.localStatus.roomparam = dwParam;
		return 0;
	}
	
	anychat.prototype.EnterRoomEx = function(lpRoomName, lpRoomPass) {
		var that = this;
		if(that.localStatus.socketConnect) {
			that.socket.sendCommand("enterroomex", {"roomname":lpRoomName, "password":lpRoomPass});
		}
		that.localStatus.roomname = lpRoomName;
		that.localStatus.roompass = lpRoomPass;
		return 0;
	}
	
	
	anychat.prototype.QueryUserStateString = function(dwUserId, dwOptName) {
		var that = this;
		if(typeof that.userInfoData[dwUserId] != "undefined") {
			if(dwOptName == BRAC_USERSTATE_NICKNAME)
				return that.userInfoData[dwUserId].nickname;
			else if(dwOptName == BRAC_USERSTATE_INTERNETIP)
				return that.userInfoData[dwUserId].internetip;
			else if(dwOptName == BRAC_USERSTATE_LOCALIP)
				return that.userInfoData[dwUserId].internetip;
		}
		return "";
	};
	
	anychat.prototype.QueryUserStateInt= function(dwUserId, dwOptName) {
		var that = this;
		if(typeof that.userInfoData[dwUserId] != "undefined") {
			if(dwOptName == BRAC_USERSTATE_LEVEL)
				return that.userInfoData[dwUserId].level;
		}
		return 0;
	};
	
	anychat.prototype.GetRoomOnlineUsers = function() {
		return this.roomusers;
	};
	
	anychat.prototype.LeaveRoom = function(dwRoomid) {
		var that = this;
		if(that.localStatus.socketConnect) {
			that.socket.sendCommand("leaveroom", {"roomid":parseInt(dwRoomid)});
		}
		clearRoomStatus();
		return 0;
	};
	
	anychat.prototype.Logout = function() {
		var that = this;
		if(that.localStatus.socketConnect) {
			that.socket.sendCommand("logout", {"errorcode":0});
		}
		that.socket.close();
		that.socket = null;
		that.localStatus.socketConnect = false;
		clearAllStatus();
		return 0;
	};
	
	anychat.prototype._attach_stream = function(parentobj, id, stream) {
		var that = this;
		var videoobj = document.getElementById(id);
		if(videoobj == null) {
			// ������Ƶ��ʾ���
			videoobj = document.createElement("video");
			videoobj.id = id;
			videoobj.style.width = "100%";
			videoobj.style.height= "100%";
			videoobj.autoplay = true;
			parentobj.appendChild(videoobj);
		}
		if(stream){
			if (navigator.mozGetUserMedia) {
				videoobj.mozSrcObject = stream;
				videoobj.play();
			}
			videoobj.src = URL.createObjectURL(stream);
		}
		return videoobj;
	}
	
	anychat.prototype.SetVideoPos = function(dwUserId, parentobj, id) {
		var that = this;
		if(!that.localStatus.socketConnect)
			return -1;
		if(dwUserId == -1 || that.localStatus.selfuserid == dwUserId) {
			that.localVideoObject = that._attach_stream(parentobj, id, that.localStatus.localMediaStream);
		} else {
			that.remoteVideoObject = that._attach_stream(parentobj, id, that.localStatus.remoteMediaStream);
		}
		return 0;
	};
	
	anychat.prototype.UserCameraControl = function(dwUserId, bOpen) {
		var that = this;
		if(!that.localStatus.socketConnect)
			return -1;
		that.socket.sendCommand("usercameracontrol", {"userid":parseInt(dwUserId), "bopen":parseInt(bOpen)});
		// ����������Ƶ
		if(dwUserId == -1 || that.localStatus.selfuserid == dwUserId) {
			if(!!bOpen && !that.localMediaStream) {
				that.createStream();
			}
		} else {
			if(!!bOpen && typeof that.peerConnections[dwUserId] == "undefined") {
				var pc = that.createPeerConnection(dwUserId);
				pc.addStream(that.localMediaStream);
				pc.createOffer(function(desc) {
					pc.setLocalDescription(desc);
					that.socket.send(JSON.stringify({
						"eventName": "__offer",
						"data": {"sdp": desc.sdp, "userid": parseInt(dwUserId)}
					}));
				});
			} else if(!bOpen && typeof that.peerConnections[dwUserId] != "undefined") {
				
			}
		}
		return 0;
	};

	anychat.prototype.UserSpeakControl = function(dwUserId, bOpen) {
		var that = this;
		if(!that.localStatus.socketConnect)
			return -1;
		that.socket.sendCommand("userspeakcontrol", {"userid":parseInt(dwUserId), "bopen":parseInt(bOpen)});
		return 0;
	};
	
	// SDK�ں˲�������
	anychat.prototype.SetSDKOptionString = function(optname, value) {
		var that = this;
		if(!that.localStatus.socketConnect) {
			var data = {"command":"setsdkoptionstring", "param":{"optname":parseInt(optname), "value":value}};
			that.sdkoptionData[optname] = data;
		} else {
			that.socket.sendCommand("setsdkoptionstring", {"optname":parseInt(optname), "value":value});
		}
		return 0;
	};
	// SDK�ں˲�������
	anychat.prototype.SetSDKOptionInt = function(optname, value) {
		var that = this;		
		if(!that.localStatus.socketConnect) {
			var data = {"command":"setsdkoptionint", "param":{"optname":parseInt(optname), "value":parseInt(value)}};
			that.sdkoptionData[optname] = data;
		} else {
			that.socket.sendCommand("setsdkoptionint", {"optname":parseInt(optname), "value":parseInt(value)});
		}
	};
	
	// ��Ƶ�����¼����ƣ����󡢻ظ����Ҷϵȣ�
	anychat.prototype.VideoCallControl = function(dwEventType, dwUserId, dwErrorCode, dwFlags, dwParam, szUserStr) {
		var that = this;
		if(!that.localStatus.socketConnect)
			return -1;
		that.socket.sendCommand("videocallcontrol", {"event":parseInt(dwEventType), "userid":parseInt(dwUserId), "errorcode":parseInt(dwErrorCode), "flags":parseInt(dwFlags), "param":parseInt(dwParam), "userstr":szUserStr});
		return 0;
	};
	// ͸��ͨ�����ͻ�����
	anychat.prototype.TransBuffer = function(dwUserId, lpBuf, dwLen) {
		var that = this;
		if(!that.localStatus.socketConnect)
			return -1;
		that.socket.sendCommand("transbuffer", {"userid":parseInt(dwUserId), "buf":lpBuf});
		return 0;
	};
	// �����ı���Ϣ
	anychat.prototype.SendTextMessage = function(dwUserId, bSecret, lpMsgBuf, dwLen) {
		var that = this;
		if(!that.localStatus.socketConnect)
			return -1;
		that.socket.sendCommand("sendtextmessage", {"userid":parseInt(dwUserId), "secret":parseInt(bSecret), "msgbuf":lpMsgBuf});
		return 0;
	};
	// ��ȡ�û�����ID�б�������һ��userid�����飩
	anychat.prototype.GetUserFriends = function(){
		var that = this;
		var friends = new Array();
		for(var userid in that.friendInfoData)
			friends.push(userid);
		return friends;
	};
	// ��ȡ��������״̬
	anychat.prototype.GetFriendStatus = function(dwFriendUserId) {
		var that = this;
		if(typeof that.friendInfoData[dwFriendUserId] != "undefined")
			return that.friendInfoData[dwFriendUserId].status;
		else
			return 0;
	};
	// ��ȡ�û�����ID�б�������һ��GroupId�����飩
	anychat.prototype.GetUserGroups = function() {
		var that = this;
		var groups = new Array();
		for(var groupid in that.groupInfoData)
			groups.push(groupid);
		return groups;
	};
	// ��ȡ��������ĺ����б�������һ��userid�����飩
	anychat.prototype.GetGroupFriends = function(dwGroupId) {
		var that = this;
		var friends = new Array();
		for(var userid in that.friendInfoData) {
			if(that.friendInfoData[userid].groupid == dwGroupId) {
				friends.push(userid);
			}
		}
		return friends;
	};
	// ��ȡ�û���Ϣ
	anychat.prototype.GetUserInfo = function(dwUserId, dwInfoId) {
		var that = this;
		if(typeof that.friendInfoData[dwUserId] != "undefined")
			return that.friendInfoData[dwUserId]["t" + dwInfoId];
		else
			return "";
	};
	// ��ȡ�û���������
	anychat.prototype.GetGroupName = function(dwGroupId) {
		var that = this;
		if(typeof that.groupInfoData[dwGroupId] != "undefined")
			return that.groupInfoData[dwGroupId].groupname;
		else
			return "";		
	};
	// �û���Ϣ����
	anychat.prototype.UserInfoControl = function(dwUserId, dwCtrlCode, wParam, lParam, lpStrValue) {
		var that = this;
		if(!that.localStatus.socketConnect)
			return -1;
		that.socket.sendCommand("userinfocontrol", {"userid":parseInt(dwUserId), "ctrlcode":parseInt(dwCtrlCode), "wparam":parseInt(wParam), "lparam":parseInt(lParam), "strvalue":lpStrValue});
		return 0;
	};
	// ��ȡҵ�����ID�б�������һ��ObjectId�����飩
	anychat.prototype.ObjectGetIdList = function(dwObjectType) {
		var that = this;
		var objectids = new Array();
		for(var i in that.objectInfoData) {
			if(that.objectInfoData[i].objecttype == dwObjectType) {
				objectids.push(that.objectInfoData[i].objectid);
			}
		}
		return objectids;
	};
	// ��ȡҵ��������ֵ������ֵ��
	anychat.prototype.GetObjectIntValue = function(dwObjectType, dwObjectId, dwInfoName) {
		var that = this;
		var value = 0;
		for(var i in that.objectInfoData) {
			if(that.objectInfoData[i].objecttype == dwObjectType && that.objectInfoData[i].objectid == dwObjectId) {
				if(dwInfoName == ANYCHAT_OBJECT_INFO_FLAGS)
					value = that.objectInfoData[i].flags;
				else if(dwInfoName == ANYCHAT_OBJECT_INFO_PRIORITY)
					value = that.objectInfoData[i].priority;
				else if(dwInfoName == ANYCHAT_OBJECT_INFO_ATTRIBUTE)
					value = that.objectInfoData[i].attribute;
				else if(dwInfoName == ANYCHAT_OBJECT_INFO_INTTAG)
					value = that.objectInfoData[i].inttag;
				else if(dwInfoName == ANYCHAT_QUEUE_INFO_WAITTIMESECOND)
					value = that.queueWaitSeconds;
				else {
					for(var k in that.objectInfoData[i].status) {
						if(parseInt(k) == dwInfoName) {
							value = parseInt(that.objectInfoData[i].status[k]);
							break;
						}
					}
				}
				break;
			}
		}
		return value;
	};
	// ��ȡҵ��������ֵ���ַ�����
	anychat.prototype.GetObjectStringValue = function(dwObjectType, dwObjectId, dwInfoName) {
		var that = this;
		var value = "";
		for(var i in that.objectInfoData) {
			if(that.objectInfoData[i].objecttype == dwObjectType && that.objectInfoData[i].objectid == dwObjectId) {
				if(dwInfoName == ANYCHAT_OBJECT_INFO_NAME)
					value = that.objectInfoData[i].objectname;
				else if(dwInfoName == ANYCHAT_OBJECT_INFO_DESCRIPTION)
					value = that.objectInfoData[i].objectdesc;
				else if(dwInfoName == ANYCHAT_OBJECT_INFO_STRINGTAG)
					value = that.objectInfoData[i].strtag;
				else {
					for(var k in that.objectInfoData[i].status) {
						if(parseInt(k) == dwInfoName) {
							value = that.objectInfoData[i].status[k];
							break;
						}
					}
				}
				break;
			}
		}
		return value;
	};
	// ����ҵ��������ֵ
	anychat.prototype.SetObjectStringValue = function(dwObjectType, dwObjectId, dwInfoName, value) {
		var that = this;
		if(!that.localStatus.socketConnect)
			return -1;
		that.socket.sendCommand("setobjectstrvalue", {"objecttype":parseInt(dwObjectType), "objectid":parseInt(dwObjectId), "infoname":parseInt(dwInfoName), "value":value});
		return 0;
	};
	// ����ҵ��������ֵ
	anychat.prototype.SetObjectIntValue = function(dwObjectType, dwObjectId, dwInfoName, value) {
		var that = this;
		if(!that.localStatus.socketConnect)
			return -1;
		that.socket.sendCommand("setobjectintvalue", {"objecttype":parseInt(dwObjectType), "objectid":parseInt(dwObjectId), "infoname":parseInt(dwInfoName), "value":parseInt(value)});
		return 0;
	};
	// ҵ��������ָ��
	anychat.prototype.ObjectControl = function(dwObjectType, dwObjectId, dwCtrlCode, dwParam1, dwParam2, dwParam3, dwParam4, strParam) {
		var that = this;
		if(!that.localStatus.socketConnect)
			return -1;
		that.socket.sendCommand("objectcontrol", {"objecttype":parseInt(dwObjectType), "objectid":parseInt(dwObjectId), "ctrlcode":parseInt(dwCtrlCode), 
				"param1":parseInt(dwParam1), "param2":parseInt(dwParam2), "param3":parseInt(dwParam3), "param4":parseInt(dwParam4), "strparam":strParam});
		return 0;
	};
	
	
    return new anychat();
};