import * as vscode from 'vscode';
import { getScope } from './hscopes';
import { switchIM, getIM } from './switch-koffi';

let cursorColor = vscode.workspace.getConfiguration().get("Settings.CursorColor") ?? undefined;


let currentEn = false;
let previousEn = false;
// let currentInMath = false;
// let previousInMath = false;

/**
 * 自动切换函数，根据当前光标所在位置的代码结构自动调整视角
 *
 * @param context 扩展上下文，用于存储和访问扩展的状态和资源
 */
export function autoShift(context: vscode.ExtensionContext) {
  let scopeText_cache = ""; // 初始化缓存

  vscode.window.onDidChangeTextEditorSelection(e => {
    const hscopes = getScope(e.textEditor.document, e.selections[0].active);
    if (!hscopes) {
      console.log('Failed to get the scope, skipping...');
      return;
    }
    let scopeText = Array.isArray(hscopes) ? hscopes.join(';') : hscopes.toString();
    if (scopeText !== scopeText_cache) {
      scopeText_cache = scopeText;
      toggleCondition(scopeText);
    }
  });
}

async function toggleCondition(scopeText: string) {

  const configuration = vscode.workspace.getConfiguration('workbench');
  let backConfig: any = configuration.get('colorCustomizations');
  // 增加识别'math'的判断
  currentEn = scopeText.includes('comment') || scopeText.includes('math');
  if (currentEn) {
    configuration.update('colorCustomizations', { ...backConfig, "editorCursor.foreground": cursorColor || undefined }, true);
  } else {
    configuration.update('colorCustomizations', { ...backConfig, "editorCursor.foreground": undefined }, true);
  }
  if (currentEn === previousEn) { return; }
  switchIM(currentEn);
  previousEn = currentEn;
}

function showInfo(str: string, res = 'Continue', rej = 'Exit') {
  return new Promise(function (resolve, reject) {
    vscode.window.showInformationMessage(str, res, rej).then(result => {
      (result === res) ? resolve(res) : reject(rej);
    });
  });
}