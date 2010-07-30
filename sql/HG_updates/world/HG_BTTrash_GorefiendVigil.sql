-- Shadowmoon Champion Formation #1
DELETE FROM `creature_formations` WHERE `leaderguid`='12882';
INSERT INTO `creature_formations` VALUES ('12882', '12882', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('12882', '12874', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('12882', '12870', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('12882', '12877', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('12882', '53801', '0', '0', '2');

DELETE FROM `creature_template_addon` WHERE `entry`='23018';
INSERT INTO `creature_template_addon` VALUES ('23018', '0', '14334', '0', '0', '0', '0', '0', '0');

-- Wolf Patrol #1
DELETE FROM `creature_addon` WHERE `guid`='53800';
INSERT INTO `creature_addon` VALUES ('53800', '53800', '14334', '0', '0', '0', '0', '0', '0');

UPDATE `creature` SET `movementtype`='2' WHERE `guid`='53800';

DELETE FROM `waypoint_data` WHERE `id`='53800';
INSERT INTO `waypoint_data` VALUES ('53800', '1', '581.336', '111.016', '139.311', '3000', '0', '0', '100', '0');
INSERT INTO `waypoint_data` VALUES ('53800', '2', '575.414', '111.236', '139.436', '0', '0', '0', '100', '0');
INSERT INTO `waypoint_data` VALUES ('53800', '3', '542.094', '111.295', '165.938', '0', '0', '0', '100', '0');
INSERT INTO `waypoint_data` VALUES ('53800', '4', '514.463', '112.324', '164.771', '0', '0', '0', '100', '0');
INSERT INTO `waypoint_data` VALUES ('53800', '5', '514.762', '170.275', '163.981', '0', '0', '0', '100', '0');
INSERT INTO `waypoint_data` VALUES ('53800', '6', '473.248', '173.234', '163.981', '3000', '0', '0', '100', '0');

-- Shadowmoon BloodMage #1
DELETE FROM `creature_formations` WHERE `leaderguid`='12871';
INSERT INTO `creature_formations` VALUES ('12871', '12871', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('12871', '52443', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('12871', '52759', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('12871', '52753', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('12871', '52752', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('12871', '52758', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('12871', '52454', '0', '0', '2');

-- Shadowmoon BloodMage #2
DELETE FROM `creature_formations` WHERE `leaderguid`='52745';
INSERT INTO `creature_formations` VALUES ('52745', '52745', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('52745', '52744', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('52745', '52754', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('52745', '12883', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('52745', '52755', '0', '0', '2');

-- Shadowmoon Champion #2
DELETE FROM `creature_formations` WHERE `leaderguid`='12879';
INSERT INTO `creature_formations` VALUES ('12879', '12879', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('12879', '52442', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('12879', '12876', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('12879', '12875', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('12879', '52444', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('12879', '52756', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('12879', '52757', '0', '0', '2');

-- Skeleton #1
DELETE FROM `creature_formations` WHERE `leaderguid`='52766';
INSERT INTO `creature_formations` VALUES ('52766', '52766', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('52766', '52747', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('52766', '12890', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('52766', '52746', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('52766', '12891', '0', '0', '2');

-- Shadowmoon Houndmaster #1
DELETE FROM `creature_formations` WHERE `leaderguid`='52440';
INSERT INTO `creature_formations` VALUES ('52440', '52440', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('52440', '53799', '0', '0', '2');

-- Shadowmoon Champion #3
DELETE FROM `creature_formations` WHERE `leaderguid`='12873';
INSERT INTO `creature_formations` VALUES ('12873', '12873', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('12873', '12881', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('12873', '12872', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('12873', '12880', '0', '0', '2');

-- Shadowmoon Houndmaster #2 Patrol
UPDATE `creature` SET `position_x`='435.145', `position_y`='239.251', `position_z`='164.766' WHERE `guid`='53798';
UPDATE `creature` SET `position_x`='439.471', `position_y`='239.271', `position_z`='164.766' WHERE `guid`='53797';
UPDATE `creature` SET `position_x`='430.601', `position_y`='240.918', `position_z`='164.764' WHERE `guid`='53796';

DELETE FROM `creature_addon` WHERE `guid`='53798';
INSERT INTO `creature_addon` VALUES ('53798', '53798', '14334', '0', '0', '0', '0', '0', '0');
UPDATE `creature` SET `movementtype`='2' WHERE `guid`='53798';

DELETE FROM `creature_formations` WHERE `leaderguid`='53798';
INSERT INTO `creature_formations` VALUES ('53798', '53798', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('53798', '53796', '5', '0.79', '2');
INSERT INTO `creature_formations` VALUES ('53798', '53797', '5', '5.50', '2');

DELETE FROM `waypoint_data` WHERE `id`='53798';
INSERT INTO `waypoint_data` VALUES ('53798', '1', '434.906', '238.973', '164.768', '3000', '0', '0', '100', '0');
INSERT INTO `waypoint_data` VALUES ('53798', '2', '434.939', '243.248', '164.76', '1000', '0', '0', '100', '0');
INSERT INTO `waypoint_data` VALUES ('53798', '3', '436.006', '310.327', '192.775', '0', '0', '0', '100', '0');
INSERT INTO `waypoint_data` VALUES ('53798', '4', '436.817', '317.047', '192.775', '3000', '0', '0', '100', '0');
INSERT INTO `waypoint_data` VALUES ('53798', '5', '436.027', '310.498', '192.775', '1000', '0', '0', '100', '0');
INSERT INTO `waypoint_data` VALUES ('53798', '6', '435.499', '243.365', '164.759', '0', '0', '0', '100', '0');

-- Shadowmoon Champion #4
DELETE FROM `creature_formations` WHERE `leaderguid`='12878';
INSERT INTO `creature_formations` VALUES ('12878', '12878', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('12878', '52749', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('12878', '13232', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('12878', '52748', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('12878', '13231', '0', '0', '2');

UPDATE `creature_addon` SET `path_id`='12878' WHERE `guid`='12878';
UPDATE `creature` SET `movementtype`='2' WHERE `guid`='12878';

DELETE FROM `waypoint_data` WHERE `id`='12878';
INSERT INTO `waypoint_data` VALUES ('12878', '1', '436.822', '349.812', '192.756', '0', '0', '0', '100', '0');
INSERT INTO `waypoint_data` VALUES ('12878', '2', '446.373', '355.195', '192.756', '0', '0', '0', '100', '0');
INSERT INTO `waypoint_data` VALUES ('12878', '3', '446.952', '365.401', '192.756', '0', '0', '0', '100', '0');
INSERT INTO `waypoint_data` VALUES ('12878', '4', '441.441', '372.439', '192.756', '0', '0', '0', '100', '0');
INSERT INTO `waypoint_data` VALUES ('12878', '5', '429.204', '372.692', '192.755', '0', '0', '0', '100', '0');
INSERT INTO `waypoint_data` VALUES ('12878', '6', '423.112', '363.184', '192.756', '0', '0', '0', '100', '0');
INSERT INTO `waypoint_data` VALUES ('12878', '7', '427.973', '351.316', '192.757', '0', '0', '0', '100', '0');

-- Skeleton #2
DELETE FROM `creature_formations` WHERE `leaderguid`='52767';
INSERT INTO `creature_formations` VALUES ('52767', '52767', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('52767', '13233', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('52767', '52750', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('52767', '52751', '0', '0', '2');
INSERT INTO `creature_formations` VALUES ('52767', '13234', '0', '0', '2');


