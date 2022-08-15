# DataModifier4BlindBoxAuction

基于QT/C++的，为弹幕游戏——盲盒拍卖会设计和开发的游戏数据修改器。当前具有以下功能：
* 以表格的形式呈现经过排序的玩家积分与成就信息。并支持更改
* 在操作中备份数据，导出csv文件可供分发
* 合并其它数据文件到当前数据中
* 批量的添加、删除积分或者成就数据
* 支持MOD成就的读取，但可能存在BUG隐患



本项目未设置License（许可证）。但仍欢迎有DALAO能协助追加功能或者修复BUG。

本项目代码仅供个人学习交流与软件使用者的协助更新与BUG报告。

<h2>TO DO LIST/Pull requests说明</h2>
以下为可能的更新方向。期待有大佬的Pull requests的帮助。

类型  | 描述
---   | ---
BUG   |当删除成就数据时，如果使用中成就为删除的成就，并不会导致使用中成就的改变。
BUG   |对于不连续ID的成就数据的读取、保存与更改可能仍有未发现的BUG
新功能|移除成就的功能（读写成就文件）
新功能|修改、管理箱子数据的功能（能够更改箱子的类型，游戏内只能初次设置箱子类型）

<h3>代码说明</h3>

- 创建代码的QT版本：Qt 5.12.12（Qt Creator 5.0.2 (Community)）
- 不建议添加非QT的头文件
- 建议使用较复杂的类名，并尽量增强代码可读性
- 如果更改MODmenu类的界面，必须将组件放置在布局管理器中
